# Music player

`ZKMediaPlayer:: E_MEDIA_TYPE_AUDIO`タイプの` ZKMediaPlayer`クラスオブジェクトを生成します

```c++
static ZKMediaPlayer sPlayer(ZKMediaPlayer::E_MEDIA_TYPE_AUDIO);
```

メッセージ監視関数を登録します。
```c++
// The message monitoring interface is as follows
class PlayerMessageListener : public ZKMediaPlayer::IPlayerMessageListener {
public:
    virtual void onPlayerMessage(ZKMediaPlayer *pMediaPlayer, int msg, void *pMsgData) {
        switch (msg) {
        case ZKMediaPlayer::E_MSGTYPE_ERROR_INVALID_FILEPATH:
        case ZKMediaPlayer::E_MSGTYPE_ERROR_MEDIA_ERROR:
            // Error message
            break;

        case ZKMediaPlayer::E_MSGTYPE_PLAY_STARTED:
            // Start playback message
            break;

        case ZKMediaPlayer::E_MSGTYPE_PLAY_COMPLETED:
            // Stop playback message
            break;
        }
    }
};
static PlayerMessageListener sPlayerMessageListener;


// Register message monitoring
sPlayer.setPlayerMessageListener(&sPlayerMessageListener);
```
メンバ関数の説明
```c++
sPlayer.play("/mnt/extsd/music/test.mp3");	// Play the file in the specified path
sPlayer.pause();	// Pause playback
sPlayer.resume();	// Resume playback
sPlayer.seekTo(int msec);	// Jump to msec time to play, msec unit: ms
sPlayer.stop();	// Stop playback
sPlayer.isPlaying();	// Is it playing?, return type is bool

sPlayer.getDuration();		// Get the total time of current playing music
sPlayer.getCurrentPosition();	// Get the current playing time of the currently playing song

sPlayer.setVolume(0.5, 0.5);	// Set media volume, volume range: 0.0 ~ 1.0
```

> [!Note]
> オーディオファイルの再生時間が短すぎる場合、プレイができない場合があります。

[Sample Code](demo_download＃demo_download.md)の`MusicDemo`プロジェクト参照してください