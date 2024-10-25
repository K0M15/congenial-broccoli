#include <libc.h>
#include <errno.h>
#include <assert.h>
#include "get_next_line.h"
#include "get_next_line.c"

// void test_get_next_line()
// {	

// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// }

// t_lasttime	*test_create_new_buffer()
// {
// 	static t_lasttime *data;
// 	void *result;
// 	if(data == NULL)
// 		result = create_new_buffer(&data);
// 	assert(data != NULL);
// 	assert(data->allocated == 2*1000*1000);
// 	assert(data->buffer != NULL);
// 	assert(data->filled == 0);
// 	return (data);
// }

// void test_read_into_buffer(t_lasttime *data, int fd)
// {
// 	read_into_buffer(data, 42, fd);
// }

// void test_get_string(t_lasttime *data)
// {
// 	size_t read_bytes;
// 	char *res;
// 	int status;

// 	read_bytes = data->filled;
// 	status = get_string(data, &res);
// 	while(status)
// 	{
// 		assert(status != -1);
// 		printf("%s", res);
// 		assert(data->filled == read_bytes - strlen(res));
// 		free(res);
// 		read_bytes = data->filled;
// 		status = get_string(data, &res);
// 	}
// }

// int run_single()
// {
// 	int filedes = open("test_file", O_RDONLY);
// 	if (filedes == -1)
// 		return errno;
// 	t_lasttime *data = test_create_new_buffer();
// 	test_read_into_buffer(data, filedes);
// 	test_get_string(data);
// 	test_read_into_buffer(data, filedes);
// 	test_get_string(data);
// 	free_buffer(data);
// 	close(filedes);
// 	return 0;
// }

void readwholefile(const char *file)
{
	char *x;
	int i = 1;
	//run_single()
	setbuf(stdout, NULL);
	int filedes = open(file, O_RDONLY);
	if(filedes == -1)
		return ;
	x = get_next_line(filedes);
	while(i && x)
	{
		printf("%s", x);
		free(x); 
		x = get_next_line(filedes);
		i++;
	}
	close(filedes);
}

int main()
{
	// readwholefile("test_file");
	// readwholefile("tf_2");
	readwholefile("tf_empty");
	// readwholefile("tf_empty2");
}
