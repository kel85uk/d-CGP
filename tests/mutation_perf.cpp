#define BOOST_TEST_MODULE dcgp_mutation_perf
#include <boost/test/unit_test.hpp>
#include <boost/timer/timer.hpp>

#include "../src/dcgp.hpp"


void perform_active_mutations(unsigned int in,
                  unsigned int out,
                  unsigned int rows,
                  unsigned int columns,
                  unsigned int levels_back,
                  unsigned int N,
                  std::vector<dcgp::basis_function> function_set)
{
    // Instatiate the expression
    dcgp::expression ex(in, out, rows, columns, levels_back, function_set, 123);
    std::cout << "Performing " << N << " mutations, in:" << in << " out:" << out << " rows:" << rows << " columns:" << columns << std::endl;
    {
      boost::timer::auto_cpu_timer t;
      for (auto i = 0u; i < N; ++i){
          ex.mutate_active();
      }
    }
}

/// This torture test is passed whenever it completes. It is meant to check for
/// the code stability when large number of mutations are performed
BOOST_AUTO_TEST_CASE(mutation_speed)
{
    dcgp::function_set basic_set({"sum","diff","mul","div"});
    perform_active_mutations(2,4,2,3,4, 100000, basic_set());
    perform_active_mutations(2,4,10,10,11, 100000, basic_set());
    perform_active_mutations(2,4,20,20,21, 100000, basic_set());
    perform_active_mutations(1,1,1,100,101, 100000, basic_set());
    perform_active_mutations(1,1,2,100,101, 100000, basic_set());
    perform_active_mutations(1,1,3,100,101, 100000, basic_set());
    perform_active_mutations(1,1,100,100,101, 100000, basic_set());
}

