import time
from rich.console import Console
from subsystems.label import label

from rich.live import Live

def main(robotData):
    console = Console()
    console.clear()
    with Live(refresh_per_second=10) as live:
        while True:
            lines = [
                f"Status: {round(robotData[label.NAME.value], 3)}",
                f"X:      {round(robotData[label.XPOS.value], 3)}",
                f"Y:      {round(robotData[label.YPOS.value], 3)}",
                f"H:      {round(robotData[label.HEADING.value], 3)}",
                f"right:  {round(robotData[label.RIGHTVEL.value], 3)}",
                f"left:   {round(robotData[label.LEFTVEL.value], 3)}",
                f"clamp:  {round(robotData[label.CLAMP.value], 3)}",
            ]
            live.update("\n".join(lines))
            time.sleep(0.05)

