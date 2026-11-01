# kio-stl-thumbnailer

STL thumbnails for Dolphin and other KDE Plasma 6 / KIO file views.

KDE 6 ignores freedesktop `.thumbnailer` files and ships no STL thumbnail
plugin, and `stl-thumb` (GL-based) renders blank images under many
Wayland/Mesa setups. This package is a small KIO thumbnail plugin that calls
`stl-thumbnailer`, a pure software renderer (numpy + Pillow, no GL).

- Binary and ASCII STL (`model/stl`, `application/sla`)
- Painter's-algorithm render with a teal, lit isometric view
- Large meshes are vertex-clustered first, so a 1M-triangle model takes ~4 s

## Install

Arch / Manjaro (AUR): `yay -S kio-stl-thumbnailer`

From source:

    cmake -S . -B build -DCMAKE_INSTALL_PREFIX=/usr
    cmake --build build
    sudo cmake --install build

Then restart Dolphin. Make sure previews are enabled in
Configure → Interface → Previews, and raise the preview size limit if needed
(`kwriteconfig6 --file kdeglobals --group PreviewSettings --key MaximumSize 104857600`).

Standalone use: `stl-thumbnailer SIZE input.stl output.png`

## License

MIT
