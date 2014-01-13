// - basic_curl.cc : Report MIME type of a remote file using libcurl

// Standard Library
#include <iostream>
#include <stdexcept>

// Third Party
// - cURL
#include <curl/curl.h>

// This Project
// trashcan for writedata
size_t curl_trashcan(void* /*buffer*/, size_t size, size_t nmemb, void* /*userptr*/) {
  return size*nmemb;
}

int main(int argc, char **argv)
{
  // Init curl
  CURL* curlHandle(curl_easy_init());
  if (!curlHandle) {
    std::cerr << "Failed to easy_init libcurl" << std::endl;
    return 1;
  }

  // - Configure libcurl
  //curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1);
  curl_easy_setopt(curlHandle, CURLOPT_NOPROGRESS, 1);

  // handle data
  curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, curl_trashcan);

  // So the metadata header is included
  curl_easy_setopt(curlHandle, CURLOPT_HEADER, 1);

  // So body is ignored (for HTTP(S))
  curl_easy_setopt(curlHandle, CURLOPT_NOBODY, 1);

  // - Perform curl operation
  curl_easy_setopt(curlHandle, CURLOPT_URL, argv[1]);
  CURLcode curlResult = curl_easy_perform(curlHandle);
  if (curlResult) {
    std::cerr << "curl failed : " << curlResult << " (" << curl_easy_strerror(curlResult) << ")" << std::endl;
  }

  long resultCode(0);
  CURLcode infoResult = curl_easy_getinfo(curlHandle,
                                          CURLINFO_RESPONSE_CODE,
                                          &resultCode);

  std::cout << "Checking CURLINFO_RESPONSE_CODE : \n"
            << "  CURLcode    : " << infoResult << "\n"
            << "  value(long) : " << resultCode << std::endl;

  char* ctType(0);
  infoResult = curl_easy_getinfo(curlHandle,
                                 CURLINFO_CONTENT_TYPE,
                                 &ctType);

  std::cout << "Checking CURLINFO_CONTENT_TYPE : \n"
            << "  CURLcode    : " << infoResult << "\n"
            << "  value(char*) : " << ctType << std::endl;



  // - Teardown libcurl
  curl_easy_cleanup(curlHandle);
  return 0;
}

