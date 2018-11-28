// #include <iostream>
// #include <utility>
// #include <functional>
// #include <fstream>
// #include <memory>
// #include <boost/graph/adjacency_matrix.hpp>
// #include <boost/graph/graph_utility.hpp>
// #include "../include/graph.hpp"
// // #include "../include/file_reader.hpp"

// void test();
// void test2();

// int main() {
//     // struct A {
//     //     int a,b,c;
//     //     void func(std::ifstream&) {
//     //         a = 5;
//     //         b = 0;
//     //         c = 5;
//     //         std::cout << a << b << c << std::endl;
//     //     }
//     // };
//     // A example;
//     // auto xd = std::bind(&A::func, example, std::placeholders::_1);
//     // std::cout << fr::Load("../../../ATTENDANCE.txt", xd) << std::endl;
//     test2();
//     return 0;
// }

// void test() {
//     enum { A, B, C, D, E, F, N };
//     const char* name = "ABCDEF";
    
//     typedef boost::adjacency_matrix<boost::directedS> Graph;
//     Graph g(N);
//     boost::add_edge(B, C, g);
//     boost::add_edge(B, F, g);
//     boost::add_edge(C, A, g);
//     boost::add_edge(C, C, g);
//     boost::add_edge(D, E, g);
//     boost::add_edge(E, D, g);
//     boost::add_edge(F, A, g);

//     //Print test
//     std::cout << "vertex set: ";
//     boost::print_vertices(g, name);
//     std::cout << std::endl;

//     std::cout << "edge set: ";
//     boost::print_edges(g, name);
//     std::cout << std::endl;

//     std::cout << "out-edges: " << std::endl;
//     boost::print_graph(g, name);
//     std::cout << std::endl;
// }

// void test2() {
//     std::unique_ptr<mg::Graph> gr;
//     try 
//     {
//         gr = std::make_unique<mg::Graph>("test_data/test2.txt");
//     }
//     catch (std::runtime_error& e)
//     {
//         std::cerr << e.what() << std::endl;
//         std::exit(1);
//     }
//     //gr->gen_random_complete_graph();
//     gr->print_vertices(std::cout);
//     gr->print_edges(std::cout);
//     gr->print_out_edges(std::cout);
// }
#include "boost/program_options.hpp" 
 
#include <iostream> 
#include <string> 

namespace 
{ 
  const std::size_t ERROR_IN_COMMAND_LINE = 1; 
  const std::size_t SUCCESS = 0; 
  const std::size_t ERROR_UNHANDLED_EXCEPTION = 2; 
 
} // namespace 
 
int main(int argc, char** argv) 
{ 
  try 
  { 
    /** Define and parse the program options 
     */ 
    namespace po = boost::program_options; 
    po::options_description desc("Options"); 
    desc.add_options() 
      ("help,h", "Print help messages")
      ("") 
      ("add", "additional options") 
      ("like", "this"); 
 
    po::variables_map vm; 
    try 
<<<<<<< HEAD
    {
        gr = std::make_unique<mg::Graph>("test_data/test.txt");
    }
    catch (std::runtime_error& e)
    {
        // std::cerr << e.what() << std::endl;
        // std::exit(1);
    }
    //gr->gen_random_complete_graph();
    gr->print_vertices(std::cout);
    gr->print_edges(std::cout);
    gr->print_out_edges(std::cout);
}
=======
    { 
      po::store(po::parse_command_line(argc, argv, desc),  
                vm); // can throw 
 
      /** --help option 
       */ 
      if ( vm.count("help") || vm.empty() ) 
      { 
        std::cout << "Basic Command Line Parameter App" << std::endl 
                  << desc << std::endl; 
        return SUCCESS; 
      } 
 
      po::notify(vm); // throws on error, so do after help in case 
                      // there are any problems 
    } 
    catch(po::error& e) 
    { 
      std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
      std::cerr << desc << std::endl; 
      return ERROR_IN_COMMAND_LINE; 
    } 
 
    // application code here // 
 
  } 
  catch(std::exception& e) 
  { 
    std::cerr << "Unhandled Exception reached the top of main: " 
              << e.what() << ", application will now exit" << std::endl; 
    return ERROR_UNHANDLED_EXCEPTION; 
 
  } 
 
  return SUCCESS; 
 
} // main 
>>>>>>> 112ee4362cfe738cd597ad9422de873694cd9289
