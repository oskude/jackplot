#include <stdio.h>
#include <jack/jack.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

// TODO: how bad is this code?
// TODO: what is completely wrong?
// TODO: whats a better solution?
// TODO: render() is sometimes called more than once before next process() is called
// TODO: can we feed the whole data to opengl? (without for loop)

int x;
int num_frames;
jack_client_t *client;
jack_port_t *input_port;
jack_default_audio_sample_t *in;
jack_default_audio_sample_t *last;
jack_default_audio_sample_t *ptr;

void
render ()
{
	last = in + num_frames;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	x = 0;
	for (ptr = in; ptr < last; ptr++) {
		glVertex2f(x, *ptr);
		x++;
	}
	glEnd();
	glFlush();
}

int
process (jack_nframes_t nframes, void *arg)
{
	in = jack_port_get_buffer(input_port, nframes);
	num_frames = nframes;
	return 0;
}

// https://github.com/iiiypuk/glfw-examples/blob/master/fps_counter.c
int frames = 0;
double t, t0, fps;
char title_string[10];
int show_fps (GLFWwindow* window)
{
	t = glfwGetTime();
	if((t - t0) > 1.0 || frames == 0)
	{
		fps = (double)frames / (t - t0);
		sprintf(title_string, "FPS: %.1f", fps);
		glfwSetWindowTitle(window, title_string);
		t0 = t;
		frames = 0;
	}
	frames++;
}

int
main (void)
{
	GLFWwindow* window;
	jack_status_t  status;
	jack_options_t options = JackNullOption;

	// Setup JACK
	client = jack_client_open("jackplot", options, &status, NULL);
	jack_set_process_callback(client, process, 0);
	input_port = jack_port_register(client, "audio_1", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
	jack_activate(client);

	// Setup GLFW
	glfwInit();
	window = glfwCreateWindow(1024, 512, "jackplot", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // TODO: what happens if we remove this?

	// Setup OpenGL
	glColor3f(1.0, 1.0, 1.0);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0, 1024, -1.0, 1.0);
	glFlush();
	glfwSwapBuffers(window);

	// Press play on tape
	while (!glfwWindowShouldClose(window))
	{
		render();
		glfwSwapBuffers(window);
		show_fps(window);
		glfwPollEvents();
	}

	// Done
	jack_client_close(client);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
