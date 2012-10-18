#include <dcs/system/posix_process.hpp>
#include <dcs/test.hpp>
#include <iostream>
#include <string>
#include <vector>

static const ::std::string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed rutrum quam non eros volutpat non feugiat lectus aliquam. Fusce in lacus at eros pharetra gravida nec vel metus. Vestibulum mattis odio ultrices libero fermentum et euismod justo vulputate. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Vivamus vel purus augue, pellentesque consectetur nisi. Vivamus velit augue, lobortis at ornare et, pharetra id purus. Maecenas varius dui eu nisi facilisis quis tempus lectus auctor. Cras suscipit mi sit amet nisl vehicula vitae dapibus enim sodales. Mauris quis aliquet felis. Suspendisse ornare sem eget dolor tempus eu laoreet quam pharetra. In hac habitasse platea dictumst.\n\
	Sed hendrerit ultrices dolor et commodo. Quisque lobortis ipsum sed magna aliquet posuere. Nulla auctor venenatis placerat. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Quisque bibendum suscipit fermentum. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Maecenas dolor enim, hendrerit vitae dapibus eu, fringilla ac odio. Nam porttitor posuere ante, at tincidunt leo pretium nec. Nam viverra, diam quis iaculis rhoncus, dui justo pulvinar nulla, sed facilisis nisl turpis in sapien. Nam eu lorem quis tortor posuere aliquam id vel libero. Sed sed ipsum risus. Sed hendrerit eros in augue tristique luctus. Nam viverra arcu a odio porttitor consectetur. Morbi congue odio et eros rutrum varius. Duis vel tempor magna.\n\
	Mauris libero augue, blandit sed porttitor et, tristique at mi. Vestibulum mattis sem in enim elementum eget auctor tortor laoreet. Fusce a magna vel tortor auctor aliquam. Sed sit amet ligula urna, a tincidunt tortor. Curabitur ut ante sit amet nunc dapibus faucibus. Quisque accumsan sodales metus, in dignissim mauris elementum sed. Nam pretium pulvinar ligula sed dapibus.\n\
	Phasellus ultrices pellentesque sagittis. Morbi tellus lorem, rhoncus eu rutrum at, vestibulum id velit. Nullam in justo ac urna ornare malesuada. Nullam non arcu arcu. Duis fringilla, lorem eu ultrices vehicula, diam orci congue nibh, id sodales sapien enim ut arcu. Ut ut ipsum tortor, non vehicula purus. Etiam ipsum lorem, blandit vel faucibus eu, interdum nec libero. Nam eget lorem tellus. Fusce vitae nisi et ipsum posuere bibendum sed et erat. Pellentesque dui elit, ornare rutrum lobortis eget, gravida eget dui. Donec at arcu tellus, id dapibus erat.\n\
	Donec eleifend elementum vestibulum. Pellentesque sit amet elit ut massa pretium consequat eu id diam. In turpis ligula, ultrices et commodo rutrum, commodo at neque. Nulla facilisi. Sed lacus ipsum, suscipit vitae interdum sit amet, euismod laoreet justo. Integer ac tellus lacus, at condimentum nibh. Phasellus faucibus ante vitae justo fringilla pharetra. Nam feugiat, velit a pretium vulputate, est augue aliquet dui, et venenatis erat lacus vel nunc.";


DCS_TEST_DEF( test_run )
{
	DCS_TEST_TRACE("Test Case: run");

	dcs::system::posix_process proc("hostname");

	proc.run();

	DCS_TEST_CHECK( true );
}

DCS_TEST_DEF( test_alive )
{
	DCS_TEST_TRACE("Test Case: alive");

	dcs::system::posix_process proc("cat");

	proc.run();

	DCS_TEST_CHECK_EQ( true, proc.alive() );

	proc.terminate();

	DCS_TEST_CHECK_EQ( false, proc.alive() );
}

DCS_TEST_DEF( test_input_producer )
{
	dcs::system::posix_process proc("cat");

	proc.asynch(true);
	std::vector<std::string> args;
	proc.run(args.begin(), args.end(), true);

	std::ostream& ois = proc.input_stream();

	ois << text;

	DCS_TEST_CHECK( true );
}

DCS_TEST_DEF( test_output_consumer )
{
	dcs::system::posix_process proc("ls");

	proc.asynch(true);
	std::vector<std::string> args;
	proc.run(args.begin(), args.end(), false, true);

	std::istream& ios = proc.output_stream();

	while (ios.good())
	{
		::std::string buf;
		ios >> buf;
		DCS_DEBUG_TRACE("Read: " << buf);
	}

	DCS_TEST_CHECK( true );
}

DCS_TEST_DEF( test_error_consumer )
{
	dcs::system::posix_process proc("such_command_does_not_exist");

	proc.asynch(true);
	std::vector<std::string> args;
	proc.run(args.begin(), args.end(), false, false, true);

	std::istream& eos = proc.error_stream();

	while (eos.good())
	{
		::std::string buf;
		eos >> buf;
		DCS_DEBUG_TRACE("Read: " << buf);
	}

	DCS_TEST_CHECK( true );
}


int main()
{
	DCS_TEST_BEGIN();
		DCS_TEST_DO( test_run );
		DCS_TEST_DO( test_alive );
//		DCS_TEST_DO( test_input_producer ); FIXME: does not work
		DCS_TEST_DO( test_output_consumer );
		DCS_TEST_DO( test_error_consumer );
	DCS_TEST_END();
}
