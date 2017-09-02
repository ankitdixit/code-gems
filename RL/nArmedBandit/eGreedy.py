import random
from matplotlib import pyplot as plt
import numpy as np


class agent():
    def __init__(self, machines, exploration):
        self.exploration = exploration
        # creats an estimate of n machines
        self.machines = np.zeros(machines)
        self.counts = [0] * machines

    def action(self):
        best = self.machines.argmax()
        if np.random.random_sample() < self.exploration:
            chosen = np.random.random_integers(0, len(self.machines) - 2)
            return chosen if chosen < best else chosen + 1
        return best

    def update(self, machine, reward):
        self.counts[machine] += 1
        self.machines[machine] += (reward - self.machines[machine]) / self.counts[machine]


class environment():
    def __init__(self, machines):
        self.machines = np.random.normal(size=machines)

    def optimal_action(self):
        return np.argmax(self.machines)

    def reward(self, action):
        return self.machines[action] + np.random.normal()


def experiment(n_runs, n_machines, n_steps, exploration):
    optimals = np.zeros((n_runs, n_steps))
    for run in range(n_runs):
        env = environment(n_machines)
        aj = agent(n_machines, exploration)
        for step in range(n_steps):
            action = aj.action()
            if action == env.optimal_action():
                optimals[run,step] = 100
            aj.update(action, env.reward(action))
    return np.mean(optimals, 0)


def main():
    for e in (0, .01, .1):
        plt.plot(experiment(n_runs=1000, n_machines=10, n_steps=1000, exploration=e))

    plt.gca().set_ylim([0,100])
    plt.legend(['greedy', 'explore 1%', 'explore 10%'], loc='upper left')
    plt.show()


if __name__ == '__main__':
    main()