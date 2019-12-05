#include "platform.h"
#include <stdio.h>
#include <unistd.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

getProcAddressProc lovrGetProcAddress = eglGetProcAddress;

static struct {
  EGLDisplay display;
  EGLContext context;
  EGLSurface surface;
} state;

bool lovrPlatformInit() {
  return true;
}

void lovrPlatformDestroy() {
  if (state.display) eglMakeCurrent(state.display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
  if (state.surface) eglDestroySurface(state.display, state.surface);
  if (state.context) eglDestroyContext(state.display, state.context);
  if (state.display) eglTerminate(state.display);
  memset(&state, 0, sizeof(state));
}

const char* lovrPlatformGetName() {
  return "Android";
}

void lovrPlatformPollEvents() {
  //
}

/* Temporarily implemented elsewhere
double lovrPlatformGetTime() {

}

void lovrPlatformSetTime(double t) {

}
*/

void lovrPlatformOpenConsole() {
  //
}

bool lovrPlatformCreateWindow(WindowFlags* flags) {
  if (state.display) {
    return true;
  }

  if ((state.display = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY) {
    return false;
  }

  if (eglInitialize(state.display, NULL, NULL) == EGL_FALSE) {
    return false;
  }

  EGLConfig configs[1024];
  EGLint configCount;
  if (eglGetConfigs(state.display, configs, sizeof(configs) / sizeof(configs[0]), &configCount) == EGL_FALSE) {
    return false;
  }

  const EGLint attributes[] = {
    EGL_RED_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_BLUE_SIZE, 8,
    EGL_ALPHA_SIZE, 8,
    EGL_DEPTH_SIZE, 0,
    EGL_STENCIL_SIZE, 0,
    EGL_SAMPLES, 0,
    EGL_NONE
  };

  EGLconfig config = 0;
  for (EGLint i = 0; i < configCount && !config; i++) {
    EGLint value, mask;

    mask = EGL_OPENGL_ES3_BIT_KHR;
    if (!eglGetConfigAttrib(state.display, configs[i], EGL_RENDERABLE_TYPE, &value) || (value & mask) != mask) {
      continue;
    }

    mask = EGL_PBUFFER_BIT | EGL_WINDOW_BIT;
    if (!eglGetConfigAttrib(state.display, configs[i], EGL_SURFACE_TYPE, &value) || (value & mask) != mask) {
      continue;
    }

    for (int a = 0; a < sizeof(attributes) / sizeof(attributes[0]); a += 2) {
      if (attributes[a] == EGL_NONE) {
        config = configs[i];
        break;
      }

      if (!eglGetConfigAttrib(state.display, configs[i], attributes[a], &value) || value != attributes[a + 1]) {
        break;
      }
    }
  }

  EGLint contextAttributes[] = {
    EGL_CONTEXT_CLIENT_VERSION, 3,
    EGL_NONE
  };

  if ((state.context = eglCreateContext(state.display, configs[i], EGL_NO_CONTEXT, contextAttributes)) == EGL_NO_CONTEXT) {
    return false;
  }

  EGLint surfaceAttributes[] = {
    EGL_WIDTH, 16,
    EGL_HEIGHT, 16,
    EGL_NONE
  };

  if ((state.surface = eglCreatePbufferSurface(state.display, config, surfaceAttributes)) == EGL_NO_SURFACE) {
    eglDestroyContext(state.context);
    return false;
  }

  if (eglMakeCurrent(state.display, state.surface, state.surface, state.context) == EGL_FALSE) {
    eglDestroySurface(state.surface);
    eglDestroyContext(state.context);
  }

  return true;
}

void lovrPlatformGetWindowSize(int* width, int* height) {
  if (width) *width = 0;
  if (height) *height = 0;
}

/* Temporarily implemented elsewhere
void lovrPlatformGetFramebufferSize(int* width, int* height) {
  *width = *height = 0;
}
*/

void lovrPlatformSwapBuffers() {
  //
}

void lovrPlatformOnWindowClose(windowCloseCallback callback) {
  //
}

void lovrPlatformOnWindowResize(windowResizeCallback callback) {
  //
}

void lovrPlatformOnMouseButton(mouseButtonCallback callback) {
  //
}

void lovrPlatformOnKeyboardEvent(keyboardCallback callback) {
  //
}

void lovrPlatformGetMousePosition(double* x, double* y) {
  *x = *y = 0.;
}

void lovrPlatformSetMouseMode(MouseMode mode) {
  //
}

bool lovrPlatformIsMouseDown(MouseButton button) {
  return false;
}

bool lovrPlatformIsKeyDown(KeyCode key) {
  return false;
}

void lovrPlatformSleep(double seconds) {
  usleep((unsigned int) (seconds * 1000000));
}

int lovrPlatformGetExecutablePath(char* dest, uint32_t size) {
  return 1;
}
