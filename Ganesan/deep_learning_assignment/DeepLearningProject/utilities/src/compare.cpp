#include "compare.h"

bool compare_outputs(const std::vector<float>& output, const std::vector<float>& reference, float tolerance) {
    if (output.size() != reference.size()) {
        std::cerr << "❌ ERROR: Output size (" << output.size() << ") does not match reference size (" << reference.size() << ")!" << std::endl;
        return false;
    }

    for (size_t i = 0; i < output.size(); ++i) {
        if (std::fabs(output[i] - reference[i]) > tolerance) {
            std::cerr << "❌ ERROR at index " << i << ": Output = " << output[i] << ", Reference = " << reference[i] << std::endl;
            return false;
        }
    }

    return true;
}
