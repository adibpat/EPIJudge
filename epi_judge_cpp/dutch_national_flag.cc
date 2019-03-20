#include <array>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
typedef enum { kRed, kWhite, kBlue } Color;

void swap (Color& a, Color& b) 
{
  Color temp = a;
  a = b;
  b = temp;
}

void DutchFlagPartition(int pivot_index, vector<Color>* A_ptr) {
  auto &A = *A_ptr;
  int small = 0, i = 0, end = A.size() -1;
  int pivot = A[pivot_index];
#ifdef DBG
  std::cout << "Pivot index " << pivot_index << std::endl;
  for (;i<=end;i++) {
    std::cout << A[i] << " ";
  }
  std::cout << std::endl;
#endif
  for (i=0;i<=end;) {
    if (A[i] < pivot) {
      //std::cout << "Swap "<< A[i] << " and " << A[small] << std::endl;
      swap(A[i], A[small]);
      small++; i++;
    } else if (A[i] == pivot) {
      //std::cout << "Skip swap for index " << i << std::endl;
      i++;
    } else {
      //std::cout << "Swap "<< A[i] << " and " << A[end] << std::endl;
      swap(A[i], A[end]);
      end--;
    }
  }
#ifdef DBG  
  for (i=0;i<=end;i++) {
    std::cout << A[i] << " ";
  }
  std::cout << std::endl;
#endif
}

void DutchFlagPartitionWrapper(TimedExecutor& executor, const vector<int>& A,
                               int pivot_idx) {
  vector<Color> colors;
  colors.resize(A.size());
  std::array<int, 3> count = {0, 0, 0};
  for (size_t i = 0; i < A.size(); i++) {
    count[A[i]]++;
    colors[i] = static_cast<Color>(A[i]);
  }
  Color pivot = colors[pivot_idx];

  executor.Run([&] { DutchFlagPartition(pivot_idx, &colors); });

  int i = 0;
  while (i < colors.size() && colors[i] < pivot) {
    count[colors[i]]--;
    ++i;
  }

  while (i < colors.size() && colors[i] == pivot) {
    count[colors[i]]--;
    ++i;
  }

  while (i < colors.size() && colors[i] > pivot) {
    count[colors[i]]--;
    ++i;
  }

  if (i != colors.size()) {
    throw TestFailure("Not partitioned after " + std::to_string(i) +
                      "th element");
  } else if (count != std::array<int, 3>{0, 0, 0}) {
    throw TestFailure("Some elements are missing from original array");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A", "pivot_idx"};
  return GenericTestMain(args, "dutch_national_flag.cc",
                         "dutch_national_flag.tsv", &DutchFlagPartitionWrapper,
                         DefaultComparator{}, param_names);
}
