{
  description = "A template for Nix based C project setup.";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, ... }@inputs: inputs.utils.lib.eachSystem [
    "x86_64-linux" "i686-linux" "aarch64-linux" "x86_64-darwin"
  ] (system: let pkgs = import nixpkgs {
                   inherit system;
                 };
             in {
               devShell = pkgs.mkShell rec {
                 name = "tictactoe";

                 packages = with pkgs; [
                   gnumake
                   gcc
                 ];
               };
             });
}
