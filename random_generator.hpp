#pragma once

#include <random>
#include <iostream>

using Num = std::uint_fast32_t; 
using Engine = std::mt19937 ;

int Myfinvt() {
  std::random_device os_seed;
  const Num seed = os_seed();
  
  Engine generator( seed );
  std::uniform_int_distribution<Num> distribute(33, 126 );

  for( int repetition = 0; repetition < 100; ++repetition )
    std::cout << char(distribute( generator ));
  return 0;
}