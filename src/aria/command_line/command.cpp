#include <utility>

#include <aria/command_line/command.hpp>

namespace aria::command_line
{

[[nodiscard]] bool is_command_line_flag(str const flag) noexcept
{
	return flag.size() >= 2 && ((flag[1UL] == '-' && flag[0UL] == '-') || flag[0UL] == '-');
}

std::pair<command, szt> parse_flag(const char* const args[], szt current)
{
	str const flag = args[current];

	command cmd {};

	const bool is_flag = is_command_line_flag(flag);

	auto const parse_value_flag = [&cmd, &flag]() -> bool
	{
		const auto val_sep_index = flag.find_first_of('=');

		if (val_sep_index == std::string_view::npos) { return false; }

		cmd.name  = flag.substr(0, val_sep_index);
		cmd.value = flag.substr(val_sep_index + 1, flag.length());

		return true;
	};

	if (is_flag)
	{
		if (parse_value_flag()) { return {cmd, current}; }

		cmd.name = flag;
	}

	const char* const next_arg = args[current + 1UL];

	const bool is_value = (next_arg != nullptr) && next_arg[0UL] != '-';
	if (is_value)
	{
		cmd.value = next_arg;
		++current;
	}

	return {cmd, current};
}

std::optional<command_line_t> parse(const s32 argc, const char* const argv[])
{
	if (argc == 0) { return {}; }

	command_line_t flags {};

	if (argc == 2)
	{
		str const flag = argv[1UL];
		return is_command_line_flag(flag) ? (flags.push_back({flag}), std::move(flags))
										  : std::optional<command_line_t> {};
	}

	for (s32 i {1}; i < argc; ++i)
	{
		auto [cmd, index] = parse_flag(argv, static_cast<szt>(i));
		flags.push_back(cmd);
		i = index;
	}

	return (flags.empty() ? std::optional<command_line_t> {}
						  : std::optional<command_line_t> {flags});
}

} // namespace aria::command_line
