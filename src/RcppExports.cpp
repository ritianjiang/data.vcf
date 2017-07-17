// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include "data.vcf_types.h"
#include <Rcpp.h>

using namespace Rcpp;

// open_file
XPtr_gz_reader open_file(std::string path);
RcppExport SEXP data_vcf_open_file(SEXP pathSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type path(pathSEXP);
    rcpp_result_gen = Rcpp::wrap(open_file(path));
    return rcpp_result_gen;
END_RCPP
}
// close_file
void close_file(XPtr_gz_reader reader);
RcppExport SEXP data_vcf_close_file(SEXP readerSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< XPtr_gz_reader >::type reader(readerSEXP);
    close_file(reader);
    return R_NilValue;
END_RCPP
}
// read_lines
std::vector<std::string> read_lines(XPtr_gz_reader reader, unsigned int n);
RcppExport SEXP data_vcf_read_lines(SEXP readerSEXP, SEXP nSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< XPtr_gz_reader >::type reader(readerSEXP);
    Rcpp::traits::input_parameter< unsigned int >::type n(nSEXP);
    rcpp_result_gen = Rcpp::wrap(read_lines(reader, n));
    return rcpp_result_gen;
END_RCPP
}
// resize_list_string
std::vector<std::vector<std::string> > resize_list_string(std::vector<std::vector<std::string> >& x, std::vector<int> n, std::string fill);
RcppExport SEXP data_vcf_resize_list_string(SEXP xSEXP, SEXP nSEXP, SEXP fillSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<std::vector<std::string> >& >::type x(xSEXP);
    Rcpp::traits::input_parameter< std::vector<int> >::type n(nSEXP);
    Rcpp::traits::input_parameter< std::string >::type fill(fillSEXP);
    rcpp_result_gen = Rcpp::wrap(resize_list_string(x, n, fill));
    return rcpp_result_gen;
END_RCPP
}
// split_info
Rcpp::List split_info(std::vector<std::string>& x);
RcppExport SEXP data_vcf_split_info(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<std::string>& >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(split_info(x));
    return rcpp_result_gen;
END_RCPP
}
// split_sample
std::vector<std::vector<std::string> > split_sample(std::vector<std::string>& x, std::string sep, std::vector<unsigned int>& n, std::string fill);
RcppExport SEXP data_vcf_split_sample(SEXP xSEXP, SEXP sepSEXP, SEXP nSEXP, SEXP fillSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<std::string>& >::type x(xSEXP);
    Rcpp::traits::input_parameter< std::string >::type sep(sepSEXP);
    Rcpp::traits::input_parameter< std::vector<unsigned int>& >::type n(nSEXP);
    Rcpp::traits::input_parameter< std::string >::type fill(fillSEXP);
    rcpp_result_gen = Rcpp::wrap(split_sample(x, sep, n, fill));
    return rcpp_result_gen;
END_RCPP
}
// collapse_group
std::vector<std::vector<std::string> > collapse_group(std::vector<std::vector<std::string> >& x, std::vector<std::vector<unsigned int> >& g, std::string sep, std::string fill);
RcppExport SEXP data_vcf_collapse_group(SEXP xSEXP, SEXP gSEXP, SEXP sepSEXP, SEXP fillSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<std::vector<std::string> >& >::type x(xSEXP);
    Rcpp::traits::input_parameter< std::vector<std::vector<unsigned int> >& >::type g(gSEXP);
    Rcpp::traits::input_parameter< std::string >::type sep(sepSEXP);
    Rcpp::traits::input_parameter< std::string >::type fill(fillSEXP);
    rcpp_result_gen = Rcpp::wrap(collapse_group(x, g, sep, fill));
    return rcpp_result_gen;
END_RCPP
}
