#include <Rcpp.h>
#include <zlib.h>
#include <Rinternals.h> // R_ExpandFileName
#include "split.h"
#include "data.vcf_types.h"

using namespace Rcpp;

//' open a vcf file
//' @param path the path for vcf file
//' @return a reader object for vcf reading
// [[Rcpp::export]]
XPtr_gz_reader open_file(std::string path){
  gz_reader *gr =  new gz_reader;
  gr->remains = "";

  gr->path = R_ExpandFileName(path.c_str());

  gzFile file = gzopen(gr->path, "r");

  if(! file){
    Rcpp::stop("gzopen failed");
  }else{
    gr->con = file;
    gzbuffer(file, 64*1024);
  }

  XPtr_gz_reader out(gr);

  return out;
}

// [[Rcpp::export]]
void close_file(XPtr_gz_reader reader){
  gzclose(reader->con);
}

//' read n lines from the file.
//' @param reader a pointer returned by open_vcf.
//' @param n how many lines to read default: n=0 for file end
//' @return a character vector, return a empty vector (length=0) when reading a file that had reached EOF; return a vector of length 1 with "" for blank line.
// [[Rcpp::export]]
std::vector<std::string> read_lines(
    XPtr_gz_reader reader,
    unsigned int n){
  std::vector<std::string> lines;

  while(n == 0 || lines.size() < n){
    if(gzeof(reader->con) && reader->remains.size() == 0){
      break;
    }

    Rcpp::checkUserInterrupt();

    int bytes_read;
    char buffer[LENGTH];
    bytes_read = gzread (reader->con, buffer, LENGTH - 1);
    buffer[bytes_read] = '\0';

    if(bytes_read < LENGTH -1 && !gzeof (reader->con)){
      // stop if gzerror
      int err;
      const char * error_string;
      error_string = gzerror (reader->con, &err);
      if (err) {
        Rcpp::Rcerr << "Error: " << error_string << ".\n";
        Rcpp::stop("gzread err");
      }
    }

    // paste remains and buffer
    std::string remainder_buffer = reader->remains + std::string(buffer);

    // split lines
    char * p1 = &remainder_buffer[0]; // forward ptr for line end
    char * p2 = &remainder_buffer[0]; // ptr for line start

    while(*p1 != '\0' && (n == 0 || lines.size() < n)){
      if(*p1 == '\n'){
        *p1 = '\0';
        lines.push_back(std::string(p2));
        p2 = p1;
        p2++;
      }
      p1++;
    }

    reader->remains = std::string(p2);
  }
  return(lines);
}

// [[Rcpp::export]]
std::vector<std::vector<std::string> > resize_list_string (
    std::vector<std::vector<std::string> > &x,
    std::vector<int> n,
    std::string fill=""){
  if(x.size() != n.size()){
    Rcpp::stop("the length of n must be equal with the length of x");
  }

  std::vector<std::vector<std::string> > out(x.size());

  for(int i=0; i < n.size(); i++){
    std::vector<std::string> out_i(n[i], fill);
    for(int j=0; j < n[i] && j < x[i].size(); j++){
      out_i[j] = x[i][j];
    }
    out[i] = out_i;
  }

  return out;
}

// [[Rcpp::export]]
Rcpp::List split_info (std::vector<std::string>& x){
  std::vector<int> iv;
  std::vector<std::string> kv;
  std::vector<std::string> vv;

  for(int i=0; i < x.size(); i++){
    std::vector<std::string> xi = split(x[i], ";");
    for(int j=0; j < xi.size(); j++){
      std::string k="";
      std::string v="";

      //std::vector<std::string> xij = split(xi[j], "=");
      //k = xij[0];
      //if(xij.size() == 2){
      //  v=xij[1];
      //}

      std::string::size_type pos = 0;
      pos = xi[j].find_first_of("=");
      if(pos == std::string::npos){
        k = xi[j];
      }else{
        k = xi[j].substr(0, pos);
        if(pos < xi[j].size()){
          v = xi[j].substr(pos+1);
        }
      }

      iv.push_back(i+1);
      kv.push_back(k);
      vv.push_back(v);
    }
  }
  return Rcpp::List::create(Rcpp::Named("i") = iv,
                            Rcpp::Named("k") = kv,
                            Rcpp::Named("v") = vv);
}

//' 7x slower than strsplit so not used
// [[Rcpp::export]]
std::vector<std::vector<std::string> > split_sample (
    std::vector<std::string> &x,
    std::string sep,
    std::vector<unsigned int> &n,
    std::string fill=""){
  if(x.size() != n.size()){
    Rcpp::stop("the length of n must be equal with the length of x");
  }
  std::vector<std::vector<std::string> > out(x.size());

  for(int i=0; i < n.size(); i++){
    std::vector<std::string> xis = split(x[i], sep);
    std::vector<std::string> out_i(n[i], fill);
    for(int j=0; j < n[i] && j < xis.size(); j++){
      out_i[j] = xis[j];
    }
    out[i] = out_i;
  }
  return out;
}

//' looply collapse each vector of a list by a group of indexs
//' @param x list
//' @param g list
//' @param sep string
//' @param fill string
//' @return list
//'
// [[Rcpp::export]]
std::vector<std::vector<std::string> > collapse_group(
    std::vector<std::vector<std::string> > &x,
    std::vector<std::vector<unsigned int> > &g,
    std::string sep="",
    std::string fill=""){
  std::vector<std::vector<std::string> > out(x.size());
  for(int i=0; i<x.size(); i++){ // loop x
    std::vector<std::string> out_i(g.size(), fill);
    for(int j=0; j < g.size(); j++){ // loop group
      std::string s = g[j].size() > 0 ? x[i][g[j][0]-1] : "";
      for(int k=1; k < g[j].size(); k++){
        s += sep;
        s += x[i][g[j][k]-1];
      }
      out_i[j] = s;
    }
    out[i] = out_i;
  }
  return out;
}

