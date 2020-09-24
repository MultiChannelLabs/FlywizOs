# Music player(音频播放)

Create a `ZKMediaPlayer` object  of type `ZKMediaPlayer::E_MEDIA_TYPE_AUDIO`

(创建 `ZKMediaPlayer`对象，类型为 `ZKMediaPlayer::E_MEDIA_TYPE_AUDIO`)

```c++
static ZKMediaPlayer sPlayer(ZKMediaPlayer::E_MEDIA_TYPE_AUDIO);
```

注册消息监听
```c++
// The message monitoring interface is as follows(消息监听接口如下)
class PlayerMessageListener : public ZKMediaPlayer::IPlayerMessageListener {
public:
    virtual void onPlayerMessage(ZKMediaPlayer *pMediaPlayer, int msg, void *pMsgData) {
        switch (msg) {
        case ZKMediaPlayer::E_MSGTYPE_ERROR_INVALID_FILEPATH:
        case ZKMediaPlayer::E_MSGTYPE_ERROR_MEDIA_ERROR:
            // Error message(出错消息)
            break;

        case ZKMediaPlayer::E_MSGTYPE_PLAY_STARTED:
            // Start playback message(开始播放消息)
            break;

        case ZKMediaPlayer::E_MSGTYPE_PLAY_COMPLETED:
            // Stop playback message(播放结束消息)
            break;
        }
    }
};
static PlayerMessageListener sPlayerMessageListener;


// Register message monitoring(注册消息监听)
sPlayer.setPlayerMessageListener(&sPlayerMessageListener);
```
操作接口说明
```c++
sPlayer.play("/mnt/extsd/music/test.mp3");	// Play the file in the specified path(播放指定路径的文件)
sPlayer.pause();	// Pause playback(暂停播放)
sPlayer.resume();	// Resume playback(恢复播放)
sPlayer.seekTo(int msec);	// Jump to msec time to play, msec unit: ms(跳转到msec时间播放， msec 单位: ms)
sPlayer.stop();	// Stop playback(停止播放)
sPlayer.isPlaying();	// Is it playing?, return type is bool(是否播放中，返回bool型)

sPlayer.getDuration();		// Get the total time of current playing music(获取当前播放歌曲的总时间)
sPlayer.getCurrentPosition();	// Get the current playing time of the currently playing song(获取当前播放歌曲的当前播放时间点)

sPlayer.setVolume(0.5, 0.5);	// Set media volume, volume range: 0.0 ~ 1.0(设置媒体音量，音量范围：0.0 ~ 1.0)
```

> [!Note]
> The audio file to be played cannot be too short. Too short may cause impossible to playing.(播放的音频文件不能过短，时间过短可能导致无法正常播放。)

For the complete code, see [Sample Code](demo_download#demo_download.md) `MusicDemo` project in the sample(完整代码见[样例代码](demo_download#demo_download.md) 控件样例里的 `MusicDemo` 工程)