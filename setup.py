import subprocess
import sys


def run_command(command: str) -> subprocess.CompletedProcess[str]:
    """
    Runs a command in the shell and captures output.
    """
    try:
        print(f"Executing: {command}")

        result = subprocess.run(
            command, 
            shell=True, 
            text=True, 
            check=True, 
            stdout=subprocess.PIPE, 
            stderr=subprocess.PIPE
        )

        print(result.stdout)
    except subprocess.CalledProcessError as e:
        print(f"Error executing command: {command}", file=sys.stderr)

        print(e.stderr, file=sys.stderr)

        sys.exit(1)


if __name__ == "__main__":
    freeglut_repo = "https://github.com/freeglut/freeglut.git"
    