import time

class Timer:
    def __init__(self):
        self.start_time = 0
        self.end_time = 0
        self.running = False

    def start(self):
        self.start_time = time.time()
        self.running = True

    def stop(self):
        self.end_time = time.time()
        self.running = False

    def get_time(self):
        if self.running:
            return time.time() - self.start_time
        else:
            return self.end_time - self.start_time

    def __str__(self):
        minutes, seconds = divmod(self.get_time(), 60)
        return f"Time Taken: {int(minutes):02}:{seconds:06.3f}"
