// Standard Library
#include <iostream>
#include <stdexcept>

// Third Party
// - magic
#include <magic.h>

// This Project

class FileMagicService {
 public:
  //! Default constructor
  FileMagicService() : mCookie_() {
    mCookie_ = magic_open(MAGIC_NONE);
    if (mCookie_ == NULL) {
      throw std::runtime_error("unable to initialize magic library");
    }
    if (magic_load(mCookie_,0) != 0) {
      std::string msg("cannot load magic database : "); // + magic_error(mCookie_));
      magic_close(mCookie_);
      throw std::runtime_error(msg);
    }
  }

  //! Destructor
  ~FileMagicService() {
    magic_close(mCookie_);
  }

  //! Return textual description of file type
  std::string getDescription(const std::string& file) {
    return this->runMagicFile(file);
  }

  //! Return MIME type of supplied file
  std::string getMIMEType(const std::string& file) {
    return this->runMagicFile(file, MAGIC_MIME_TYPE);
  }

  //! Return encoding of supplied file
  std::string getMIMEEncoding(const std::string& file) {
    return this->runMagicFile(file, MAGIC_MIME_TYPE | MAGIC_MIME_ENCODING);
  }

  //! Return all descriptions matched for supplied file
  std::string getMatches(const std::string& file) {
    return this->runMagicFile(file, MAGIC_CONTINUE);
  }

 private:
  //! Use magic to get filetype and update magic with supplied flags
  std::string runMagicFile(const std::string& file, int flags = MAGIC_NONE)
  {
    magic_setflags(mCookie_, flags);
    // Need to error handle this really - non-existent files etc...
    std::string tmp(magic_file(mCookie_, file.c_str()));
    magic_setflags(mCookie_, MAGIC_NONE);
    return tmp;
  }

 private:
  magic_t mCookie_;
};


int main(int argc, char *argv[]) {
  std::string myFile(argv[1]);
  if (myFile.empty()) {
    std::cerr << "No file supplied" << std::endl;
    return 1;
  }

  FileMagicService fmService;
  std::cout << fmService.getDescription(myFile) << std::endl;
  std::cout << fmService.getMIMEType(myFile) << std::endl;
  std::cout << fmService.getMIMEEncoding(myFile) << std::endl;
  std::cout << fmService.getMatches(myFile) << std::endl;

  return 0;
}

