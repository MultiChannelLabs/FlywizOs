# Music player

`ZKMediaPlayer::E_MEDIA_TYPE_AUDIO`타입의 `ZKMediaPlayer` 클래스 오브젝트를 생성합니다

```c++
static ZKMediaPlayer sPlayer(ZKMediaPlayer::E_MEDIA_TYPE_AUDIO);
```

메세지 모니터링 함수를 등록합니다.
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
멤버 함수 설명
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
> 오디오 파일의 재생시간이 너무 짧을 경우 플레이가 불가능할 수 있습니다.

[Sample Code](demo_download#demo_download.md)의 `MusicDemo` 프로젝트 참고하십시오