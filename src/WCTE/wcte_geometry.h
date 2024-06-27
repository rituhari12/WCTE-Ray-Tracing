#ifndef WCTE_GEOMETRY_H
#define WCTE_GEOMETRY_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <json/json.h>


struct WCTEGeometry : Json::Value {
 WCTEGeometry( const std::string& geomfile ) : Json::Value() {
    std::ifstream infile( geomfile );
    if (infile.is_open()==false){
      std::cout<<"Failed to open "<<geomfile<<", exiting"<<std::endl;
      exit(0);
    }
    infile >> *this;
  }

  void print_keys() const{
    for (auto const& key : this->getMemberNames() ){
      std::cout<< key << std::endl;
    }
  }
  
  float get_float( const std::string& key ) const { return this->operator[]( key ).asFloat(); }
  
  std::vector<float> get_vector( const std::string& key ) const {
    std::vector<float> retval;
    Value::const_iterator begin = this->operator[](key).begin();
    Value::const_iterator end = this->operator[](key).end();
    for( auto it = begin; it != end; it++ ){
      retval.push_back( it->asFloat() );
    }

    return retval;
  }

};



#endif
