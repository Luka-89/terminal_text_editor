echo "starting buildAndRun.sh .."

SCRIPTS_DIR="$(cd "$(dirname "$0")" && pwd)"
TTE_DIR="$(cd $SCRIPTS_DIR && cd .. && pwd)"
if bash "$TTE_DIR/scripts/build.sh";
then
bash "$TTE_DIR/scripts/run.sh"
else
echo "Failed to build -> skipping run"
fi
