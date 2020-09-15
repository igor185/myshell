#include <string>
#include <vector>

namespace internal {
    bool run_internal_program(const std::string& name, std::vector<std::string>& args);

    // without name
    int mpwd(std::vector<std::string>& args);
    int mexit(std::vector<std::string>& args);
    int mecho(std::vector<std::string>& args);
    int mexport(std::vector<std::string>& args);
    int mcd(std::vector<std::string>& args);
    int merrno(std::vector<std::string>& args);
}