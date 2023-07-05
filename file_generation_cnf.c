#include <stdio.h>
#include <time.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////
///                        DECLARATIONS                              ///
////////////////////////////////////////////////////////////////////////

#if defined(ABC_NAMESPACE)
namespace ABC_NAMESPACE
{
#elif defined(__cplusplus)
extern "C"
{
#endif

// procedures to start and stop the ABC framework
// (should be called before and after the ABC procedures are called)
void   Abc_Start();
void   Abc_Stop();

// procedures to get the ABC framework and execute commands in it
typedef struct Abc_Frame_t_ Abc_Frame_t;

Abc_Frame_t * Abc_FrameGetGlobalFrame();
int    Cmd_CommandExecute( Abc_Frame_t * pAbc, const char * sCommand );

#if defined(ABC_NAMESPACE)
}
using namespace ABC_NAMESPACE;
#elif defined(__cplusplus)
}
#endif


int main(int argc,char* argv[]) 
{
    if ( argc != 4 )
    {
        printf( "Wrong number of command-line arguments.\n" );
        return 1;
    }
    char * file_read;
    char * file_cnf;
    char * file_mapping;
    char Command[1000];

    file_read=argv[1];
    file_cnf=argv[2];
    file_mapping=argv[3];
    //printf( "Wrong number of command-line arguments.\n" );
    Abc_Frame_t * pAbc;
    Abc_Start();
    pAbc = Abc_FrameGetGlobalFrame();

    sprintf( Command, "read %s", file_read );
   
    if ( Cmd_CommandExecute( pAbc, Command ) )
    {
        fprintf( stdout, "Cannot execute command \"%s\".\n", Command );
        return 1;
    }
    else
    {
       printf("readinf file\n");
    }
    sprintf( Command, "strash");
            if ( Cmd_CommandExecute( pAbc, Command ) )
            {
                fprintf( stdout, "Cannot execute command \"%s\".\n", Command );
                return 1;
            }
    sprintf( Command, "write_cnf %s", file_cnf );
    if ( Cmd_CommandExecute( pAbc, Command ) )
    {
        fprintf( stdout, "Cannot execute command \"%s\".\n", Command );
        return 1;
    }
    sprintf( Command, "mv variable_mapping.txt %s",file_mapping);
    system(Command);
    Abc_Stop();
    return 0;
}
