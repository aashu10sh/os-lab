import dataclasses
from typing import Optional


@dataclasses.dataclass
class Process:
    pid: int
    arrival_time: int
    burst_time: int
    remaining_time: int
    completion_time: Optional[int] = None
    waiting_time: Optional[int] = None
    turnaround_time: Optional[int] = None


def find_times(processes: list[Process], time_quantum: int):
    current_time = 0
    queue = []
    remaining_processes = len(processes)

    for process in processes:
        if process.arrival_time <= current_time:
            queue.append(process)

    while remaining_processes > 0:
        if queue:
            process = queue.pop(0)

            if process.remaining_time > time_quantum:
                current_time += time_quantum
                process.remaining_time -= time_quantum
            else:
                current_time += process.remaining_time
                process.remaining_time = 0
                process.completion_time = current_time
                process.turnaround_time = process.completion_time - process.arrival_time
                process.waiting_time = process.turnaround_time - process.burst_time
                remaining_processes -= 1

            for p in processes:
                if (
                    p.arrival_time <= current_time
                    and p.remaining_time > 0
                    and p not in queue
                ):
                    queue.append(p)

            if process.remaining_time > 0:
                queue.append(process)
        else:
            current_time += 1


def find_avg_time(processes: list[Process], time_quantum: int):
    total_waiting_time = 0
    total_turnaround_time = 0

    find_times(processes, time_quantum)

    print(
        "Processes  Arrival time  Burst time  Completion time  Waiting time  Turnaround time"
    )

    for process in processes:
        if not process.waiting_time:
            continue
        total_waiting_time += process.waiting_time
        total_turnaround_time += process.turnaround_time
        print(
            f"   {process.pid}\t\t{process.arrival_time}\t\t{process.burst_time}\t\t{process.completion_time}\t\t{process.waiting_time}\t\t{process.turnaround_time}"
        )

    print(f"Average waiting time = {total_waiting_time / len(processes):.2f}")
    print(f"Average turnaround time = {total_turnaround_time / len(processes):.2f}")


def main():
    processes = [
        Process(1, 0, 10, 10),
        Process(2, 1, 4, 4),
        Process(3, 2, 5, 5),
        Process(4, 3, 3, 3),
    ]
    time_quantum = 2

    find_avg_time(processes, time_quantum)


if __name__ == "__main__":
    main()
