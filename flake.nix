{
  description = "Library Manager";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = {
    self,
    nixpkgs,
  }: let
    system = "x86_64-linux";
    pkgs = import nixpkgs {inherit system;};

    crow = pkgs.stdenv.mkDerivation rec {
      pname = "crow";
      version = "1.0+5";

      src = pkgs.fetchFromGitHub {
        owner = "CrowCpp";
        repo = "Crow";
        rev = "v${version}";
        hash = "sha256-rxA4HgdyY+Pi0M5cGtci6DRR9F947GPD25ut4gvSIP0=";
      };

      cmakeFlags = [
        "-DCROW_BUILD_EXAMPLES=OFF"
        "-DCROW_BUILD_TESTS=OFF"
      ];

      nativeBuildInputs = with pkgs; [
        cmake
        boost
        openssl
        zlib
      ];

      doCheck = false;
    };

    packages = with pkgs; [
      # SvelteKit + Tauri
      nodejs
      cargo
      rustc
      curl
      wget
      pkg-config
      dbus
      openssl_3
      glib
      gtk3
      libsoup
      webkitgtk
      librsvg

      # C/C++
      boost
      crow
      gnumake
    ];
  in {
    devShells.${system}.default = pkgs.mkShell {
      buildInputs = packages;

      shellHook = with pkgs; ''
        export XDG_DATA_DIRS=${gsettings-desktop-schemas}/share/gsettings-schemas/${gsettings-desktop-schemas.name}:${gtk3}/share/gsettings-schemas/${gtk3.name}:$XDG_DATA_DIRS;
        export GIO_MODULE_DIR="${glib-networking}/lib/gio/modules/";
      '';
    };
  };
}
