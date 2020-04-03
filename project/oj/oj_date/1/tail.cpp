int test1(Solution& solution)
{
    std::vector<int> nums{2, 7, 11, 15};
    int target = 9;
    std::vector<int> ret = solution.twoSum(nums, target);

    std::vector<int> result{0,1};
    bool correct = true;

    if(ret.size() != result.size())
    {
        correct = false;
    }

    for(size_t i = 0; i < ret.size(); ++i)
    {
        if (ret[i] != result[i])
        {
            correct = false;
            break;
        }
    }

    return static_cast<int>(correct);

}

int main(void)
{
    Solution solution;

    int ret = test1(solution);
    if(ret == 1)
    {
        std::cout << "恭喜你，通过所有测试用例:)" << std::endl;
    }
    else
    {
        std::cout << "很遗憾，您没有通过所有测试用例-_-|" << std::endl;
    }

    return 0;
}
