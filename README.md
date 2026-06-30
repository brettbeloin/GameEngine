# GameEngine

## Build the Project
```
 git clone git@github.com:brettbeloin/GameEngine.git
 cd GameEngine
 git submodule update --init --recursive
 cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
 cmake --build build
 ./build/GameEngine
```

---

## Linux Build Dependencies (Wayland)

When building SDL3 from source on Linux with a Wayland stack, the following
packages are required. These were confirmed on Fedora 44 during initial setup.

```
sudo dnf install \
    wayland-devel \
    wayland-protocols-devel \
    libxkbcommon-devel \
    mesa-libEGL-devel \
    alsa-devel \
    zlib-ng-compat-static
```

SDL3's CMake probes for all Wayland-related packages as a group
(`wayland-client`, `wayland-egl`, `wayland-cursor`, `egl`, `xkbcommon`).
If any one of them is missing, the entire Wayland backend is silently disabled
and SDL3 will fail to configure with:

```
SDL could not find X11 or Wayland development libraries on your system.
```

### Diagnostics

If you hit that error, verify each piece is discoverable via pkg-config:

```
pkg-config --modversion wayland-client
pkg-config --modversion xkbcommon
pkg-config --modversion egl
pkg-config --variable=pkgdatadir wayland-protocols
which wayland-scanner
```

Any of those returning empty or erroring means the corresponding `-devel`
package is missing.

After installing missing packages, always wipe the build directory before
reconfiguring — CMake caches failed dependency checks:

```
rm -rf build
cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```

### Confirming Wayland backend is enabled

After a successful configure, the SDL3 CMake output should include:

```
Enabled backends:
  Video drivers: wayland x11 ...
```

If it still shows only `dummy offscreen`, a dependency is still missing.

---

## Notes

- SDL3 is vendored as a git submodule at `external/SDL3` and built from
  source — no system SDL3 installation is required.
- Windows users do not need any of the above; the submodule build handles
  everything automatically.
- On a fresh clone, always run `git submodule update --init --recursive`
  before configuring, otherwise `external/SDL3` will be an empty directory
  and CMake will fail.
