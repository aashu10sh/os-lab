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


def find_next_process(processes: list[Process], current_time: int):
    min_remaining_time = float("inf")
    min_index = -1

    for i, process in enumerate(processes):
        if (process.arrival_time <= current_time) and (process.remaining_time > 0):
            if process.remaining_time < min_remaining_time:
                min_remaining_time = process.remaining_time
                min_index = i

    return min_index


def find_times(processes: list[Process]):
    current_time = 0
    while True:
        index = find_next_process(processes, current_time)
        if index == -1:
            if all(process.remaining_time == 0 for process in processes):
                break
            current_time += 1
            continue

        process = processes[index]
        process.remaining_time -= 1
        current_time += 1

        if process.remaining_time == 0:
            process.completion_time = current_time
            process.turnaround_time = process.completion_time - process.arrival_time
            process.waiting_time = process.turnaround_time - process.burst_time


def find_avg_time(processes: list[Process]):
    total_waiting_time = 0
    total_turnaround_time = 0

    find_times(processes)

    print(
        "Processes  Arrival time  Burst time  Completion time  Waiting time  Turnaround time"
    )

    for process in processes:
        total_waiting_time += process.waiting_time
        total_turnaround_time += process.turnaround_time
        print(
            f"   {process.pid}\t\t{process.arrival_time}\t\t{process.burst_time}\t\t{process.completion_time}\t\t{process.waiting_time}\t\t{process.turnaround_time}"
        )

    print(f"Average waiting time = {total_waiting_time / len(processes):.2f}")
    print(f"Average turnaround time = {total_turnaround_time / len(processes):.2f}")


def main():
    processes = [
        Process(1, 0, 8, 8),
        Process(2, 1, 4, 4),
        Process(3, 2, 9, 9),
        Process(4, 3, 5, 5),
    ]

    find_avg_time(processes)


if __name__ == "__main__":
    main()