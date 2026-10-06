boards_path:="./boards"
templates:="./templates"
default_board:="esp32-wroom-32e"

# list attached boards
board-ls:
  arduino-cli board list

# list installed cores
core-ls:
  arduino-cli core list

new-pio name:
  #!/usr/bin/env bash

  target="./{{name}}"

  if [ -d "${target}" ]; then
    echo "! target already exists: ${target}"
    exit 1
  fi

  mkdir "${target}"

  cd "${target}"

  echo "+ init platform io project"
  pio project init --board esp32dev --ide vim

  echo "+ copying template files from {{templates}}/pio/*"
  rsync -av ../templates/pio/ ./
  pio run -t compiledb


new-arduino-cli name board=default_board:
  #!/usr/bin/env bash

  target="./{{name}}"
  board_file="{{boards_path}}/{{board}}.json" 

  if [ -d "${target}" ]; then
    echo "! target already exists: ${target}"
    exit 1
  fi
  if [ ! -f "${board_file}" ]; then
    echo "! board file not found: ${board_file}"
    exit 1 
  fi

  # Config
  fqbn=$(jq -r ".fqbn" "$board_file")
  port=$(jq -r ".port" "$board_file")

  echo "Sketch:"
  echo "  name    {{name}} "
  echo "  target  ${target}"
  echo "  board   {{board}}"
  echo "  fqbn    ${fqbn}"
  echo "  port    ${port}"
  echo ""

  # Actions
  echo "+ creating sketch ..."
  arduino-cli sketch new {{name}}

  if [ ! -d "${target}" ]; then
    echo "! failed to create sketch ${target}"
    exit 1
  fi

  echo "+ copying template files from {{templates}}/arduino-cli/* --> $target"
  cp {{templates}}/arduino-cli/* "${target}"
  sed -i '' "s|__PORT__|${port}|g" "${target}/Makefile"
  sed -i '' "s|__FQBN__|${fqbn}|g" "${target}/Makefile"
  sleep 1

  # must not "quote" the fqbn in the yaml file ... it will crash neovim LSP
  echo "+ create $target/sketch.yaml"
  echo "fqbn: ${fqbn}" > "${target}/sketch.yaml"

  echo "+ create $target/compile_commands.json"
  (
    cd "${target}"
    arduino-cli compile --fqbn "${fqbn}" --build-path "./build" --only-compilation-database . 
    cp ./build/compile_commands.json . 
  )

  tree $target
  head $target/Makefile

  echo ""
  echo "Done."

