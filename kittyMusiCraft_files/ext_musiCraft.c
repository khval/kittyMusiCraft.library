

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#ifdef __amigaos4__
#include <proto/exec.h>
#include <proto/retroMode.h>
#endif

#ifdef __linux__
#include <string.h>
#include "os/linux/stuff.h"
#include <retromode.h>
#include <retromode_lib.h>
#endif

#include <amosKittens.h>
#include <amosString.h>
#include "stack.h"

#include <kittyErrors.h>

#include "cmdList.h"
#include "context.h"
#include "support.h"
#include "debug.h"

#include <proto/ptreplay.h>

#define kittyError instance->kittyError
#define api instance -> api
#define last_var instance -> last_var
#define cmdTmp instance -> cmdTmp

#define alloc_private(x) AllocVecTags( x , AVT_Type, MEMF_PRIVATE, TAG_END )
#define alloc_shared(x) AllocVecTags( x , AVT_Type, MEMF_SHARED, TAG_END )

#define getSprite(num) &(instance -> video -> sprites[num])

void find_scene_bank(struct KittyInstance *instance,struct context *context, int bank_id );

#define debug 1

#ifdef debug
	#warning compiling with debug 
	#define dprintf printf
#else
	#define dprintf(fmt,...)
#endif


void dump_blits(struct context *context);

extern void dispose_blit (void *ptr);
extern void dispose_object (void *ptr);

uint32 file_size(FILE *fd)
{
	uint32 size;
	fseek(fd , 0, SEEK_END );			
	size = ftell(fd);
	fseek(fd, 0, SEEK_SET );
	return size;
}

char *_musicraftStLoad(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance ;
	int args = instance -> stack - data -> stack  +1;
	struct stringData *file_name;
	struct kittyBank *bank = NULL;
	int bank_num = 0;
	int size;
	FILE *fd;

	printf("%s: args %d\n",__FUNCTION__,args);

	switch (args)
	{
		case 2:
			file_name = getStackString( instance, instance_stack-1);
			bank_num = getStackNum( instance, instance_stack);

			printf("St Load %s,%d\n",&file_name -> ptr,bank_num);
			
			fd = fopen( &file_name -> ptr , "r");
			if (fd)
			{
				size = file_size(fd);
				bank = data -> api.reserveAs( 0, bank_num , size, "Module", NULL );
				if (bank)
				{
					printf( "bank id: %d, type: %08x, start: %08x, length %d\n",bank -> id, bank -> type, bank -> start, bank -> length );

					if (bank -> start)
					{
						printf("loaded: %d\n",
							fread( bank -> start,size,1,fd)
							);
					}
				}
				else
				{
					printf("no bank created\n");
				}
				fclose(fd);
			}
			break;

		default:
			printf("setting error: 22\n");
			api.setError(22, data->tokenBuffer);	// wrong number of args.
			popStack( instance, instance_stack - data->stack );
			return NULL;
	}

	popStack( instance, instance_stack - data->stack );
	return NULL;
}

char *musicraftStLoad KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _musicraftStLoad, tokenBuffer );
	return tokenBuffer;
}

void free_mod( struct context *context )
{
	printf("%s:%d\n",__FUNCTION__,__LINE__);

	if ( context -> module )
	{
		PTStop( context -> module );
		PTFreeMod(context -> module );
		context -> module = NULL;
	}
}

char *_musicraftStPlay(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance ;
	struct kittyBank *bank = NULL;
	int args = instance -> stack - data -> stack  +1;
	int bank_num = 0;
	struct context *context = instance -> extensions_context[ instance -> current_extension ];

	switch (args)
	{
		case 1:
			{
				bank_num = getStackNum( instance, instance_stack);
				bank = data -> api.findBankById( bank_num );
				free_mod( context );

				if (bank) if (bank -> start)
				{
					context -> module = PTSetupMod( bank -> start );
					if (context -> module) PTPlay( context -> module );
				}
			}
			break;

		default:
			api.setError(22, data->tokenBuffer);	// wrong number of args.
			popStack( instance, instance_stack - data->stack );
			return NULL;
	}

	popStack( instance, instance_stack - data->stack );
	return NULL;
}

char *musicraftStPlay KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _musicraftStPlay, tokenBuffer );
	return tokenBuffer;
}

char *_musicraftStStop(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance ;
	struct kittyBank *bank = NULL;
	int args = instance -> stack - data -> stack  +1;
	int bank_num = 0;
	struct context *context = instance -> extensions_context[ instance -> current_extension ];

	switch (args)
	{
		case 1:
			{
				bank_num = getStackNum( instance, instance_stack);
				bank = data -> api.findBankById( bank_num );

				if (bank) if (bank -> start)
				{
					if (context -> module) PTStop( context -> module );
				}
			}
			break;

		default:
			printf("setting error: 22\n");
			api.setError(22, data->tokenBuffer);	// wrong number of args.
			popStack( instance, instance_stack - data->stack );
			return NULL;
	}

	popStack( instance, instance_stack - data->stack );
	return NULL;
}

char *musicraftStStop KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _musicraftStStop, tokenBuffer );
	return tokenBuffer;
}


char *_musicraftStPauseOff(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance ;
	struct kittyBank *bank = NULL;
	int args = instance -> stack - data -> stack  +1;
	int bank_num = 0;
	struct context *context = instance -> extensions_context[ instance -> current_extension ];

	switch (args)
	{
		case 1:
			{
				bank_num = getStackNum( instance, instance_stack);
				bank = data -> api.findBankById( bank_num );

				if (bank) if (bank -> start)
				{
					if (context -> module) PTResume( context -> module );
				}
			}
			break;

		default:
			printf("setting error: 22\n");
			api.setError(22, data->tokenBuffer);	// wrong number of args.
			popStack( instance, instance_stack - data->stack );
			return NULL;
	}

	popStack( instance, instance_stack - data->stack );
	return NULL;
}

char *musicraftStPauseOff KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _musicraftStPauseOff, tokenBuffer );
	return tokenBuffer;
}

char *_musicraftStPauseOn(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance ;
	struct kittyBank *bank = NULL;
	int args = instance -> stack - data -> stack  +1;
	int bank_num = 0;
	struct context *context = instance -> extensions_context[ instance -> current_extension ];

	switch (args)
	{
		case 1:
			{
				bank_num = getStackNum( instance, instance_stack);
				bank = data -> api.findBankById( bank_num );

				if (bank) if (bank -> start)
				{
					if (context -> module) PTPause( context -> module );
				}
			}
			break;

		default:
			printf("setting error: 22\n");
			api.setError(22, data->tokenBuffer);	// wrong number of args.
			popStack( instance, instance_stack - data->stack );
			return NULL;
	}

	popStack( instance, instance_stack - data->stack );
	return NULL;
}

char *musicraftStPauseOn KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _musicraftStPauseOn, tokenBuffer );
	return tokenBuffer;
}

char *musicraftStVoice KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *musicraftStChannel KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *musicraftStVumeterSpeed KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *musicraftStVolume KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *musicraftStGetVolume KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *musicraftStBase KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *musicraftStVersion KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

