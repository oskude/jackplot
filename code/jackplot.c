#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <jack/jack.h>

int                          buffer_size;
jack_port_t*                 jack_port;
jack_default_audio_sample_t* jack_buffer;

int
on_jack_process (
	jack_nframes_t nframes,
	         void* arg
){ //--------------------------------------------------------------------------
	jack_buffer = jack_port_get_buffer (jack_port, nframes);
	buffer_size = nframes;

	return 0;
}

void
on_opengl_resize (
	GLFWwindow* window,
	        int width,
	        int height
){ //--------------------------------------------------------------------------
	glViewport (0, 0, width, height);
}

void
setup_jack (
	jack_client_t** client
){ //--------------------------------------------------------------------------
	jack_status_t  status;
	jack_options_t options = JackNullOption;

	*client
		= jack_client_open      ("jackplot", options, &status, NULL);
	jack_set_process_callback   (*client, on_jack_process, 0);
	jack_port
		= jack_port_register    (*client, "audio_1", JACK_DEFAULT_AUDIO_TYPE,
		                         JackPortIsInput, 0);
	jack_activate               (*client);
}

void
setup_window (
	GLFWwindow** window,
	         int width
){ //--------------------------------------------------------------------------
	glfwInit                       ();
	*window = glfwCreateWindow     (width, width/2, "jackplot", NULL, NULL);
	glfwSetFramebufferSizeCallback (*window, on_opengl_resize);
	glfwMakeContextCurrent         (*window);
	glfwSwapInterval               (1);
}

void
setup_opengl (
	GLFWwindow* window,
	        int width
){ //--------------------------------------------------------------------------
	glColor3f       (1.0, 1.0, 1.0);
	glClearColor    (0.0, 0.0, 0.0, 1.0);
	glClear         (GL_COLOR_BUFFER_BIT);
	gluOrtho2D      (0, width, -1.0, 1.0);
	glFlush         ();
	glfwSwapBuffers (window);
}

void
plot_points (
){ //--------------------------------------------------------------------------
	static int                          x;
	static jack_default_audio_sample_t* y;
	static jack_default_audio_sample_t* last;

	x       = 0;
	last    = jack_buffer + buffer_size;
	glClear (GL_COLOR_BUFFER_BIT);
	glBegin (GL_POINTS);

	for (y = jack_buffer; y < last; y++) {
		glVertex2f (x, *y);
		x++;
	}

	glEnd   ();
	glFlush ();
}

int
main (
	void
){ //--------------------------------------------------------------------------
	GLFWwindow*    window;
	jack_client_t* client;

	setup_jack   (&client);
	setup_window (&window, jack_get_buffer_size (client));
	setup_opengl (window,  jack_get_buffer_size (client));

	while (!glfwWindowShouldClose (window))
	{
		plot_points     ();
		glfwSwapBuffers (window);
		glfwPollEvents  ();
	}

	glfwDestroyWindow (window);
	glfwTerminate     ();

	return 0;
}
