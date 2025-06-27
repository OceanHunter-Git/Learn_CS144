#include "reassembler.hh"
#include "debug.hh"

using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring )
{
  //debug( "unimplemented insert({}, {}, {}) called", first_index, data, is_last_substring );
  if (is_last_substring){
    is_last_substring_ = true;
    last_index_ = first_index + data.size();
  }
  reassembler_.resize(output_.writer().available_capacity());
  has_data_.resize(output_.writer().available_capacity());
  uint64_t start;
  uint64_t j;
  if (first_index >= first_index_){
    start = first_index - first_index_;
    j = 0;
  }else{
    start = 0;
    j = first_index_ - first_index;
  }

  uint64_t end = min(first_index + data.size() - first_index_, output_.writer().available_capacity());
  
  for (uint64_t i = start; j < data.size() && i < end; ++i, ++j){
    reassembler_[i] = data[j];
    has_data_[i] = true;
  }
  uint64_t length = 0;
  while (length < has_data_.size() && has_data_[length] == true){
    length++;
  }
  if (length != 0){
    output_.writer().push(string(reassembler_.begin(), reassembler_.begin() + length));
    reassembler_.erase(reassembler_.begin(), reassembler_.begin() + length);
    has_data_.erase(has_data_.begin(), has_data_.begin() + length);
    first_index_ += length;  
  }
  
  if (is_last_substring_ && last_index_ == first_index_){
    output_.writer().close();
  }
}

// How many bytes are stored in the Reassembler itself?
// This function is for testing only; don't add extra state to support it.
uint64_t Reassembler::count_bytes_pending() const
{
  debug( "unimplemented count_bytes_pending() called" );
  uint64_t cnt = 0;
  for (uint64_t i = 0; i < has_data_.size(); ++i){
    if (has_data_[i]){
      cnt++;
    }
  }
  return cnt;
}
