import dataclasses


@dataclasses.dataclass
class Process:
    pid: int
    arrival_time: int
    burst_time: int
    completion_time: int | None
    waiting_time: int | None
    turnaround_time: int | None


def find_times(processes: list[Process]):
    current_time = 0
    for process in processes:
        if current_time < process.arrival_time:
            current_time = process.arrival_time
        process.completion_time = current_time + process.burst_time
        process.turnaround_time = process.completion_time - process.arrival_time
        process.waiting_time = process.turnaround_time - process.burst_time
        current_time = process.completion_time


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
        Process(1, 0, 24, None, None, None),
        Process(2, 3, 3, None, None, None),
        Process(3, 5, 3, None, None, None),
    ]

    find_avg_time(processes)


if __name__ == "__main__":
    main()
