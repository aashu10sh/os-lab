import dataclasses
from typing import Optional


@dataclasses.dataclass
class Process:
    pid: int
    arrival_time: int
    burst_time: int
    priority: int
    completion_time: Optional[int] = None
    waiting_time: Optional[int] = None
    turnaround_time: Optional[int] = None


def find_next_process(processes: list[Process], current_time: int):
    highest_priority = -1
    min_index = -1

    for i, process in enumerate(processes):
        if (process.arrival_time <= current_time) and (process.completion_time is None):
            if process.priority > highest_priority:
                highest_priority = process.priority
                min_index = i
            elif process.priority == highest_priority:
                if process.arrival_time < processes[min_index].arrival_time:
                    min_index = i

    return min_index


def find_times(processes: list[Process]):
    current_time = 0
    remaining_processes = len(processes)

    while remaining_processes > 0:
        index = find_next_process(processes, current_time)
        if index != -1:
            process = processes[index]
            current_time += process.burst_time
            process.completion_time = current_time
            process.turnaround_time = process.completion_time - process.arrival_time
            process.waiting_time = process.turnaround_time - process.burst_time
            remaining_processes -= 1
        else:
            current_time += 1


def find_avg_time(processes: list[Process]):
    total_waiting_time = 0
    total_turnaround_time = 0

    find_times(processes)

    print(
        "Processes  Arrival time  Burst time  Priority  Completion time  Waiting time  Turnaround time"
    )

    for process in processes:
        total_waiting_time += process.waiting_time
        total_turnaround_time += process.turnaround_time
        print(
            f"   {process.pid}\t\t{process.arrival_time}\t\t{process.burst_time}\t\t{process.priority}\t\t{process.completion_time}\t\t{process.waiting_time}\t\t{process.turnaround_time}"
        )

    print(f"Average waiting time = {total_waiting_time / len(processes):.2f}")
    print(f"Average turnaround time = {total_turnaround_time / len(processes):.2f}")


# Main function
def main():
    processes = [
        Process(1, 0, 10, 3),
        Process(2, 2, 1, 1),
        Process(3, 4, 2, 4),
        Process(4, 6, 1, 5),
        Process(5, 8, 5, 2),
    ]

    find_avg_time(processes)


if __name__ == "__main__":
    main()
