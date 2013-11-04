#include <fstream>
#include <vector>
#include <cassert>
#include <cstring>
#include <stdint.h>
#include <zlib.h>

static inline bool check_signature(const char *s)
{
  return strcmp( s, "DSFF1.2" ) == 0;
}

static inline bool check_magic(const char *s)
{
  return strncmp( s, "IIII", 4 ) == 0;
}

static void process_compress(const char *outfile, const char *s, size_t l)
{
  const char *magic = s + 0x84;
  if( check_magic(magic) )
    {
    // wotsit ?
    std::ofstream out( outfile, std::ios::binary );
    out.write( s , l );
    out.close();
    }
  else
    {
    // Easy case: XML - ZLIB
    uint32_t d32;
    const char *destlen32 = s + 128 + 4;
    memcpy( (char*)&d32, destlen32, 4 );

    std::vector<char> outbuf;
    outbuf.resize( d32 );

    const char *source = s + 128 + 8;
    size_t sourceLen = l - 128 - 8;
    char *dest = &outbuf[0];
    uLong destLen = d32;
    int ret = uncompress ((Byte*)dest, &destLen, (const Byte*)source, sourceLen);
    assert(destLen == d32);
    assert(ret == Z_OK);

    std::ofstream out( outfile, std::ios::binary );
    out.write( dest, destLen );
    out.close();
    }
}

static bool read_dsff_section( std::istream & is )
{
  static unsigned int n = 0;

  char signature[8];
  is.read( signature, 8 );
  if( !is.good() ) return false;
  if( !check_signature( signature ) )
    {
    assert( 0 );
    return false;
    }

  uint32_t vals[4];
  is.read( (char*)&vals, sizeof( vals ) );
  assert( is.good() );

  char dir[128];
  is.read( dir, 128);
  assert( is.good() );

  const uint64_t s = vals[1] + vals[2];
  std::streampos pos = is.tellg();
  assert( s > pos );
  const uint64_t d = s - pos;

  std::vector<char> v;
  v.resize( d );
  is.read( &v[0], v.size() );

  if( n )
    {
    process_compress(dir, &v[0], v.size());
    }
  n++;

  return !is.eof();
}

int main(int argc, char *argv[])
{
  if( argc < 2 ) return 1;
  const char *dtsfile = argv[1];

  std::ifstream is( dtsfile, std::ios::binary );
  std::streampos pos;

  char signature[8];
  is.read( signature, 8 );
  if( !check_signature( signature ) )
    {
    assert( 0 );
    return 1;
    }

  char filename[256];
  is.read( filename, 0x100 );

  char dummy[66];
  is.read( dummy, sizeof(dummy) );

  while( read_dsff_section( is ) )
    {
    }

  return 0;
}
