{
  description = "Library Manager";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";

  outputs = {
    self,
    nixpkgs,
  }: let
    system = "x86_64-linux";

    pkgs = import nixpkgs {
      inherit system;
    };

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
  in {
    devShells.${system}.default = pkgs.mkShell {
      buildInputs = with pkgs; [
        nodejs
        cargo
        rustc
        pkg-config
        gtk3
        webkitgtk
        gnumake
        boost
        crow
      ];
    };
  };
}
