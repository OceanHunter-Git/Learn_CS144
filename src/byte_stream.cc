#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ) {}

void Writer::push( string data )
{
  // Your code here.
  if ( is_closed() || has_error() ) {
    return;
  }
  uint64_t length = min( data.size(), available_capacity() );

  if ( length > 0 ) {
    buffer_.reserve( buffer_.size() + length );
    buffer_.insert( buffer_.end(), data.begin(), data.begin() + length );
  }
  totalpushed_ += length;
}

void Writer::close()
{
  // Your code here.
  close_ = true;
}

bool Writer::is_closed() const
{
  return close_ ; // Your code here.
}

uint64_t Writer::available_capacity() const
{
  return capacity_ >= buffer_.size() ? capacity_ - buffer_.size() : 0; // Your code here.
}

uint64_t Writer::bytes_pushed() const
{
  return totalpushed_ ; // Your code here.
}

string_view Reader::peek() const
{
  // Your code here.
  if ( buffer_.empty() ) {
    return {};
  }
  return { buffer_.data(), buffer_.size() };
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  uint64_t length = min( len, buffer_.size() );
  if ( length > 0 ) {
    buffer_.erase( buffer_.begin(), buffer_.begin() + length );
  }
  totalpopped_ += length;
}

bool Reader::is_finished() const
{
  return close_ && buffer_.size() == 0; // Your code here.
}

uint64_t Reader::bytes_buffered() const
{
  return buffer_.size(); // Your code here.
}

uint64_t Reader::bytes_popped() const
{
  return totalpopped_; // Your code here.
}