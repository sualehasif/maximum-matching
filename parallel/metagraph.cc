#include "metagraph.h"

namespace gbbs {

template <class Graph>
double MetaGraph_runner(Graph& G, commandLine P){
  std::cout << "### Application: MetaGraphs" << std::endl;
  std::cout << "### Graph: " << P.getArgument(0) << std::endl;
  std::cout << "### Threads: " << num_workers() << std::endl;
  std::cout << "### n: " << G.n << std::endl;
  std::cout << "### m: " << G.m << std::endl;
  std::cout << "### ------------------------------------" << std::endl;
  std::cout << "### ------------------------------------" << std::endl;

  timer t; t.start();
  auto matching = MetaGraphMatching(G);
  double tt = t.stop();

  std::cout << "### Running Time: " << tt << std::endl;
  return tt;
}
}

int main(int argc, char* argv[]) {                                          
    gbbs::commandLine P(argc, argv, " [-s] <inFile>");                       
    char* iFile = P.getArgument(0);                                          
    bool symmetric = P.getOptionValue("-s");                                 
    bool compressed = P.getOptionValue("-c");                                 
    bool binary = P.getOptionValue("-b");                                     
    bool mmap = P.getOptionValue("-m");                                       
    bool mmapcopy = false;                                                  
    debug(std::cout << "# mmapcopy = " << mmapcopy << "\n";);                 
    size_t rounds = P.getOptionLongValue("-rounds", 3);                       
    gbbs::pcm_init();                                                         
    if (compressed) {                                                         
      if (symmetric) {                                                        
        auto G =                                                              
            gbbs::gbbs_io::read_compressed_symmetric_graph<gbbs::empty>(   
                iFile, mmap, mmapcopy);                                      
        gbbs::alloc_init(G);                                                 
        run_app(G, gbbs::MetaGraph_runner, rounds)                                              
      } else {                                                                
        auto G =                                                             
            gbbs::gbbs_io::read_compressed_asymmetric_graph<gbbs::empty>(  
                iFile, mmap, mmapcopy);                                       
        gbbs::alloc_init(G);                                                  
        run_app(G, gbbs::MetaGraph_runner, rounds)                                               
      }                                                                      
    } else {                                                                  
      if (symmetric) {                                                        
        auto G = gbbs::gbbs_io::read_unweighted_symmetric_graph(iFile, mmap,
                                                                binary);     
        gbbs::alloc_init(G);                                                  
        run_app(G, gbbs::MetaGraph_runner, rounds)                                               
      } else {                                                                
        auto G = gbbs::gbbs_io::read_unweighted_asymmetric_graph(iFile, mmap, 
                                                                 binary);     
        gbbs::alloc_init(G);                                                  
        run_app(G, gbbs::MetaGraph_runner, rounds)                                               
      }                                                                       
    }                                                                         
    gbbs::alloc_finish();
}