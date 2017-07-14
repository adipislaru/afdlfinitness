#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

class muchie
{
    char _caracter;
    int _stareUrmatoare;

    public:
        muchie( char, int );
        muchie( ) { }
        char caracter( );
        int stareUrmatoare( );
};

muchie::muchie( char c, int stare )
{
    _caracter = c;
    _stareUrmatoare = stare;
}

char muchie::caracter( )
{
    return _caracter;
}

int muchie::stareUrmatoare( )
{
    return _stareUrmatoare;
}

class AFD
{
    int nrStari, nrStariFinale, nrSimb;
    char cuvant[ 64 ];

    vector< list< muchie > > muchii;

    public:
        AFD( char* );
        AFD( ) { }
        int verifica( );

    private:
        int are_cicluri( );
        int are_bucle( );
        void dfs( int, vector< int >&, vector< int >&, int& );
};

AFD::AFD( char file[ ] )
{
    int st, send;
    char c;

    FILE* f = fopen( file, "r" );

    fscanf( f, "%s", &cuvant );

    fscanf( f, "%d %d %d", &nrStari, &nrStariFinale, &nrSimb );

    muchii.resize( nrStari + 1 );

    while( 1 )
    {
        fscanf( f, "%d %c %d", &st, &c, &send );

        if( feof( f ) )
            break;

        muchii[ st ].push_back( muchie( c, send ) );
    }

    fclose( f );
}

int AFD::verifica( )
{
    int len = strlen( cuvant ), i, stareCurenta = 0, ok = 1, ok2;

    if( cuvant[ 0 ] == '_' )
    {
        if( are_cicluri( ) || are_bucle( ) )
            return 0;

        return 1;
    }
    else
    {
        for( i = 0; i < len; i++ )
        {
            ok2 = 0;

            for( list< muchie >::iterator j = muchii[ stareCurenta ].begin( ); j != muchii[ stareCurenta ].end( ) && ok; ++j )
            {
                if( ( *j ).caracter( ) == cuvant[ i ] )
                {
                    stareCurenta = ( *j ).stareUrmatoare( );

                    ok2 = 1;

                    break;
                }
            }

            if( !ok2 )
                ok = 0;
        }

        if( stareCurenta < ( nrStari - nrStariFinale ) )
            ok = 0;

        return ok;
    }
}

int AFD::are_cicluri( )
{
    int ok = 1, i;

    vector< int > vizitat, fn;

    vizitat.resize( nrStari );
    fn.resize( nrStari );

    fill( vizitat.begin( ), vizitat.end( ), 0 );
    fill( fn.begin( ), fn.end( ), 0 );

    for( i = ( nrStari - nrStariFinale ); i < nrStari && ok; i++ )
        dfs( i, vizitat, fn, ok );

    return ( ok == 1 ) ? 0 : 1;
}

int AFD::are_bucle( )
{
    int i;

    for( i = ( nrStari - nrStariFinale ); i < nrStari; i++ )
        for( list< muchie >::iterator j = muchii[ i ].begin( ); j != muchii[ i ].end( ); ++j )
            if( ( *j ).stareUrmatoare( ) == i )
                return 1;

    return 0;
}

void AFD::dfs( int nod, vector< int >& vizitat, vector< int >& fn, int& ok )
{
    vizitat[ nod ] = 1;

    for( list< muchie >::iterator j = muchii[ nod ].begin( ); j != muchii[ nod ].end( ) && ok; ++j )
    {
        int nextNod = ( *j ).stareUrmatoare( );

        if( !vizitat[ nextNod ] )
            dfs( nextNod, vizitat, fn, ok );
        else
            if( vizitat[ nextNod ] && fn[ nextNod ] == 0 )
                ok = 0;
    }

    fn[ nod ] = 1;
}

int main( int argc, char* argv[ ] )
{
    AFD automat( argv[ 1 ] );

    cout << automat.verifica( );
}
