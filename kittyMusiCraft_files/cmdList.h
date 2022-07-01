
struct cmdData
{
	unsigned short token;
	char *name;
	int args;
	char *(*fn) KITTENS_CMD_ARGS;
};

extern struct cmdData AMOSPro_MusiCRAFT[];

extern char *musicraftStLoad KITTENS_CMD_ARGS;
extern char *musicraftStPlay KITTENS_CMD_ARGS;
extern char *musicraftStStop KITTENS_CMD_ARGS;
extern char *musicraftStPauseOn KITTENS_CMD_ARGS;
extern char *musicraftStPauseOff KITTENS_CMD_ARGS;
extern char *musicraftStVoice KITTENS_CMD_ARGS;
extern char *musicraftStChannel KITTENS_CMD_ARGS;
extern char *musicraftStVumeterSpeed KITTENS_CMD_ARGS;
extern char *musicraftStVolume KITTENS_CMD_ARGS;
extern char *musicraftStGetVolume KITTENS_CMD_ARGS;
extern char *musicraftStBase KITTENS_CMD_ARGS;
extern char *musicraftStVersion KITTENS_CMD_ARGS;

