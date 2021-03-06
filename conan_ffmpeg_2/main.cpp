extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavutil/avutil.h>
#include <libavutil/opt.h>
#include <libswresample/swresample.h>
}

#include <string>
#include <cstdio>
#include <vector>

void loadFromFile(const std::string &filename) {
    AVFrame* frame = av_frame_alloc();
    if (!frame) {
        puts("Error allocating the audio frame");
        return;
    }

    AVFormatContext* formatContext = nullptr;
    if (avformat_open_input(&formatContext, filename.c_str(), nullptr, nullptr) != 0) {
        av_frame_free(&frame);
        puts("Error opening audio file");
        return;
    }

    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        av_frame_free(&frame);
        avformat_close_input(&formatContext);
        puts("Error finding audio stream info");
        return;
    }

    // Find the audio stream
    int streamIndex = av_find_best_stream(formatContext, AVMEDIA_TYPE_AUDIO, -1,
                                          -1, nullptr, 0);
    if (streamIndex < 0) {
        av_frame_free(&frame);
        avformat_close_input(&formatContext);
        puts("Could not find any audio stream");
        return;
    }
    AVStream* audioStream = formatContext->streams[streamIndex];
    AVCodec* codec = avcodec_find_decoder(audioStream->codecpar->codec_id);
    
    // Initialize codec context for the decoder.
    AVCodecContext* codecContext = avcodec_alloc_context3(codec);
    if (!codecContext) {
        av_frame_free(&frame);
        avformat_close_input(&formatContext);
        puts("Couldn't allocate a decoding context.");
        return;
    }

    // Fill the codecCtx with the parameters of the codec used in the read file.
    if (avcodec_parameters_to_context(codecContext, audioStream->codecpar) !=
        0) {
        avcodec_close(codecContext);
        avcodec_free_context(&codecContext);
        avformat_close_input(&formatContext);
        puts("Couldn't find parametrs for context");
    }

    // Initialize the decoder.
    if (avcodec_open2(codecContext, codec, nullptr) != 0) {
        avcodec_close(codecContext);
        avcodec_free_context(&codecContext);
        avformat_close_input(&formatContext);
        puts("Couldn't open the audio codec context");
        return;
    }

    // Expose audio metadata
    size_t channels = codecContext->channels;
    size_t sampleRate = codecContext->sample_rate;

    // Start reading audio packets
    AVPacket readingPacket;
    av_init_packet(&readingPacket);

    std::vector<std::int16_t> data;

    while (av_read_frame(formatContext, &readingPacket) == 0) {
        if (readingPacket.stream_index == audioStream->index) {
            AVPacket decodingPacket = readingPacket;

            int sendPacket = avcodec_send_packet(codecContext, &decodingPacket);
            int receiveFrame = 0;

            while ((receiveFrame =
                        avcodec_receive_frame(codecContext, frame)) == 0) {
                // Decode audio packet

                if (receiveFrame == 0 && sendPacket == 0) {
                    // Write samples to audio buffer

                    for (size_t i = 0;
                         i < static_cast<size_t>(frame->nb_samples); i++) {
                        // Interleave left/right channels
                        for (size_t channel = 0; channel < channels;
                             channel++) {
                            int16_t sample = reinterpret_cast<int16_t*>(
                                frame->data[channel])[i];
                            data.push_back(sample);
                        }
                    }
                }
            }
        }
        av_packet_unref(&readingPacket);
    }

    // Cleanup
    av_frame_free(&frame);
    avcodec_close(codecContext);
    avformat_close_input(&formatContext);
}

int main(int argc, char **argv) {
    //av_register_all();

    for(auto i = 1; i < argc; ++i)
        loadFromFile(argv[i]);

    puts("success!\n");
    return 0;
}
