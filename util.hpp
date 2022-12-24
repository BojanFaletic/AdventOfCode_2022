#include <algorithm>

template <typename Container, typename Function>
void for_each_c(Container &container, Function function) {
  std::for_each(std::begin(container), std::end(container), function);
}