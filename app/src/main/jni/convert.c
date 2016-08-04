#include "com_spc_mp3convert_NativesMethods.h"
#include "lame.h"
#include <android/log.h>
#include <string.h>

#define TAG "mp3Convert" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型



void JNICALL Java_com_spc_mp3convert_NativesMethods_read
        (JNIEnv *env, jclass obj, jstring fromPath, jstring convertPath)
{
    //获取路径
    char *cwav = (*env)->GetStringUTFChars(env, fromPath, 0);
    char *cmp3 = (*env)->GetStringUTFChars(env, convertPath, 0);
    LOGE("源文件路径是%s", cwav);
    LOGE("转化件路径是%s", cmp3);

    //定义缓冲
    short int wav_buffer[8192 * 2];
    unsigned char mp3_buffer[8192];

    //加载文件
    FILE *fwav = fopen(cwav, "rb");//rb 二进制 读取
    FILE *fmp3 = fopen(cmp3, "wb");


    //初始化lame编码器
    lame_t lame = lame_init();
    //2. 设置lame mp3编码的采样率
    lame_set_in_samplerate(lame, 44100);
    lame_set_num_channels(lame, 2);
    // 3. 设置MP3的编码方式
    lame_set_VBR(lame, vbr_default);

    lame_init_params(lame);

    LOGE("Lame初始化完成");

    int read;
    int write;
    int total = 0; // 当前读的wav文件的byte数目
    //循环读取转化
    do
    {
        read = fread(wav_buffer, sizeof(short int) * 2, 8192, fwav);
        total += read * sizeof(short int) * 2;//read是实际读取的次数
        LOGE("converting ....%d", total);
        // 调用java代码 完成进度条的更新
        if (read != 0)
        {

            write = lame_encode_buffer_interleaved(lame, wav_buffer, read, mp3_buffer, 8192);
            //把转化后的mp3数据写到文件里
            fwrite(mp3_buffer, sizeof(unsigned char), write, fmp3);
        }
        if (read == 0)
        {
            lame_encode_flush(lame, mp3_buffer, 8192);
        }
    } while (read != 0);

    LOGE("convert  finish");
    lame_close(lame);
    fclose(fwav);
    fclose(fmp3);
}


//测试是否移植成功，返回版本号
JNIEXPORT jstring JNICALL Java_com_spc_mp3convert_NativesMethods_getLameVersion
        (JNIEnv *env, jclass obj)
{
    return (*env)->NewStringUTF(env, get_lame_version());
}


