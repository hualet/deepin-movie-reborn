#ifndef _DMR_VPU_PROXY_H
#define _DMR_VPU_PROXY_H 

#include <QtWidgets>
#include "vpuhelper.h"

#define MAX_FILE_PATH   256
#define MAX_ROT_BUF_NUM			2

typedef struct
{
        char yuvFileName[MAX_FILE_PATH];
        char bitstreamFileName[MAX_FILE_PATH];
        int     bitFormat;
    int avcExtension; // 0:AVC, 1:MVC   // if CDB is enabled 0:MP 1:MVC 2:BP
        int rotAngle;
        int mirDir;
        int useRot;
        int     useDering;
        int outNum;
        int checkeos;
        int mp4DeblkEnable;
        int iframeSearchEnable;
        int skipframeMode;
        int reorder;
        int     mpeg4Class;
        int mapType;
        int seqInitMode;
        int instNum;
        int bitstreamMode;

      int cacheOption;
      int cacheBypass;
      int cacheDual;
    LowDelayInfo lowDelayInfo;
        int wtlEnable;
    int maxWidth;
    int maxHeight;
        int coreIdx;
        int frameDelay;
        int cmd;
        int userFbAlloc;
        int runFilePlayTest;

} DecConfigParam;

namespace dmr {

class VpuDecoder : public QThread
{
    Q_OBJECT
public:
    VpuDecoder(const QString& name);
    ~VpuDecoder();

protected:
    void run() override;
    bool init();
    int loop();
    int seqInit();

signals:
    void frame(const QImage &);

private:
	DecConfigParam	decConfig;
    QString _filename;
    int _seqInited {0};

	DecHandle		handle		{0};
	DecOpenParam	decOP		{0};
	DecInitialInfo	initialInfo {0};
	DecOutputInfo	outputInfo	{0};
	DecParam		decParam	{0};
	BufInfo			bufInfo	    {0};
	vpu_buffer_t	vbStream	{0};

#if defined(SUPPORT_DEC_SLICE_BUFFER) || defined(SUPPORT_DEC_RESOLUTION_CHANGE)
	DecBufInfo decBufInfo;
#endif
	BYTE *			pYuv {0};
	FrameBuffer		fbPPU[MAX_ROT_BUF_NUM];
	FrameBufferAllocInfo fbAllocInfo;
	int				framebufSize  {0}, framebufWidth  {0};
    int             framebufHeight  {0}, rotbufWidth  {0}, rotbufHeight  {0};
    int             framebufFormat  {FORMAT_420}, mapType;
	int				framebufStride  {0}, rotStride  {0}, regFrameBufCount  {0};
	int				frameIdx  {0};
    int ppIdx {0}, decodeIdx {0};
	int				hScaleFactor, vScaleFactor, scaledWidth, scaledHeight;
	int				ppuEnable  {0};
	int				bsfillSize  {0};
	int				instIdx {0}, coreIdx {0};
	TiledMapConfig mapCfg;
	DRAMConfig dramCfg  {0};
};


class VpuProxy: public QWidget {
    Q_OBJECT
public:
    VpuProxy(QWidget *parent = 0);


public slots:
    void play(const QString& filename);

private:
    QLabel *_canvas {0};
};
}

#endif /* ifndef _DMR_VPU_PROXY_H */



