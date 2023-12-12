#include <iostream>

auto add(const long long& a, const long long& b) -> long long {
    // This function sums two elements. Takes a value of type "long long" and returns accordingly.
    // Example: 2 + 2 = 4.
    return a + b;
}

auto main() -> int {

    long long first_accepted_value;
    long long second_accepted_value;

    // We accept the value from the console separated by a space.
    std::cin >> first_accepted_value >> second_accepted_value;

    // We sum both values and write them into a "result" variable of type "long long";
    long long result_of_sum = add(first_accepted_value, second_accepted_value);

    // We output one number, the result of the summation.
    std::cout << result_of_sum << std::endl;

    // The program ended successfully.
    return 0;
}