"""
Copyright 2018-2020 Cristian Achim
All rights reserved
"""

import pdb
import random
import numpy as np
import matplotlib.pyplot as plt
import csv

#HyperparameterReader
#EpsilonHyperparameter
#StepsHyperparameter
#RunsHyperparameter
#BanditArmsCountHyperparameter
#AlphaHyperparameter
#StaticArmedBandit
#RndwlkArmedBandit
#ASimpleBanditAlgorithmPlotter
#ASimpleBanditAlgorithm
#ASimpleBanditAlgorithmStaticBanditRunner
#DynamicVsFixedStepSizeBanditAlgoPlotter
#FixedStepSizeBanditAlgo
#DynamicVsFixedStepSizeBanditRndWlkAlgoRunner
#LinRegrPlotter
#LinRegrOneVarComputation
#LinRegrOneVarRunner
#InitialGreedyExplorationVsEpsilonGreedyPlotter
#GreedyInitialExplorationBanditAlgo
#InitialExplorationOptimisticGreedyRunner
#CommandLineInterface

class HyperparameterReader:

    def __init__(self,
                    name,
                    is_int_not_float,
                    allowed_range,
                    default_value):
        self.name=name
        self.is_int_not_float=is_int_not_float
        (self.left_margin , self.right_margin)=\
            allowed_range
        self.default_value=default_value

    def read_hyperparameter(self):

        while True:
            print('\n')
            print('Insert hyperparameter ' +\
                self.name)

            if self.is_int_not_float:
                temp='Integer'
            else:
                temp='Floating point'
            temp=temp+' >='+str(self.left_margin)
            temp=temp+' <='+str(self.right_margin)
            print(temp)

            temp='Or enter nothing for\
                 default value '
            temp=temp+str(self.default_value)
            print(temp)

            try:
                input_value=input(\
                    'Enter the hyperparameter:')
                if input_value=='':
                    return self.default_value

                if self.is_int_not_float:
                    h_param=int(input_value)
                else:
                    h_param=float(input_value)
                if (h_param < self.left_margin or
                    h_param > self.right_margin):
                    self.error_message()
                else:
                    return h_param
            except ValueError:
                self.error_message()

    def error_message(self):
        temp='Please insert the hyperparameter'
        temp=temp+' according to the constraints.'
        print(temp)
        print('Return to retry.Ctrl-C to exit.')
        input()

class EpsilonHyperparameter():

    def read_epsilon(self):
        self.hpr=HyperparameterReader(
                    name='epsilon',
                    is_int_not_float=False,
                    allowed_range=(0.0 , 1.0),
                    default_value=0.01)
        return self.hpr.read_hyperparameter()

class StepsHyperparameter():

    def read_steps(self):
        self.hpr=HyperparameterReader(
                name='steps',
                is_int_not_float=True,
                allowed_range=(2,1000000000),
                default_value=10000)
        return self.hpr.read_hyperparameter()

class RunsHyperparameter():

    def read_runs(self):
        self.hpr=HyperparameterReader(
                    name='runs',
                    is_int_not_float=True,
                    allowed_range=(1,1000000000),
                    default_value=2000)
        return self.hpr.read_hyperparameter()

class BanditArmsCountHyperparameter():

    def read_bandit_arms_count(self):
        self.hpr=HyperparameterReader(
                    name='bandit_arms_count',
                    is_int_not_float=True,
                    allowed_range=(2,1000000000),
                    default_value=10)
        return self.hpr.read_hyperparameter()

class AlphaHyperparameter:

    def read_alpha(self):
        self.hpr=HyperparameterReader(
                    name='alpha_step_size',
                    is_int_not_float=False,
                    allowed_range=(0.0,1.0),
                    default_value=0.1)
        return self.hpr.read_hyperparameter()

class StaticArmedBandit():

    def __init__(self, arms_count, is_random_walk):
        self.base_dist_loc=0.
        self.base_dist_scale=1.
        self.arms_count=arms_count
        self.arm_means=np.zeros(self.arms_count)
        self.reset()

    def reset(self):
        for index in range(self.arms_count):
            self.arm_means[index] = np.random.normal(
                                        self.base_dist_loc,
                                        self.base_dist_scale)
        self.max_arm=np.argmax(self.arm_means)

    def arm_s_action_value(self, arm):
        return np.random.normal(
                                self.base_dist_loc,
                                self.base_dist_scale) + \
                self.arm_means[arm]

    def is_optimal_action(self, arm):
        return self.max_arm == arm

class RndwlkArmedBandit:

    def __init__(self, arms_count, is_random_walk):
        self.rndwlk_dist_loc=0.
        self.rndwlk_dist_scale=0.01
        self.arms_count=arms_count
        self.arm_means=np.zeros(self.arms_count)
        self.reset()

    def reset(self):
        self.arm_means=np.zeros(self.arms_count)
        
    def random_walk():
        for index in range(self.arms_count):
            self.arm_means[index] += np.random.normal(
                                            self.rndwlk_dist_loc,
                                            self.rndwlk_dist_scale)

    def advance_bandit(self):
        self.arm_s_action_value=np.random.normal(
                                                self.base_dist_loc,
                                                self.base_dist_scale) + \
                                self.arm_means[arm]

    def arm_s_action_value(self, arm):
        return self.arm_s_action_value

    def is_optimal_action(self, arm):
        return np.argmax(self.arm_means) == arm

class ASimpleBanditAlgorithmPlotter:

    def __init__(self, runs, steps):
        self.runs=runs
        self.steps=steps

    def plot(self, pltdt_rewards, pltdt_optimpercent):
        
        pltdt_optimpercent[0]=\
            pltdt_optimpercent[0].cumsum()
        pltdt_optimpercent[1]=\
            pltdt_optimpercent[1].cumsum()
        pltdt_optimpercent[2]=\
            pltdt_optimpercent[2].cumsum()
        for e in range(3):
            pltdt_rewards[e] /= self.runs
            for step in range(self.steps):
                pltdt_optimpercent[e][step] /= (self.runs * (step+1))
        
        plt.figure()
        plt.plot(
            pltdt_rewards[0], label='epsilon=0.0')
        plt.plot(
            pltdt_rewards[1], label='epsilon=0.01')
        plt.plot(
            pltdt_rewards[2], label='epsilon=0.1')
        plt.legend(loc='lower right')
        plt.xlabel('Steps')
        plt.ylabel('Average reward')
        plt.savefig('simple_bandit_algo_2000_runs_average_reward.pdf')

        plt.figure()
        plt.plot(
            pltdt_optimpercent[0],
            label='epsilon=0.0')
        plt.plot(
            pltdt_optimpercent[1],
            label='epsilon=0.01')
        plt.plot(
            pltdt_optimpercent[2],
            label='epsilon=0.1')
        plt.legend(loc='lower right')
        plt.xlabel('Steps')
        plt.ylabel('% Optimal action')
        plt.savefig(
            'simple_bandit_algo_2000_runs_percentage_optimal_selection.pdf')

class ASimpleBanditAlgorithm:

    def __init__(self, steps, epsilon, the_armed_bandit, arms_count):
        self.epsilon=epsilon
        self.steps=steps
        self.arms_count=arms_count
        self.the_armed_bandit=the_armed_bandit
        self.Q=np.zeros(self.arms_count)
        self.N=np.zeros(self.arms_count)

    def run(self, pltdt_rewards, pltdt_optimpercent):
        for step in range(self.steps):
            sample=random.uniform(0.0,1.0)
            if sample < self.epsilon :
                self.A=random.randint(0 , (self.arms_count-1))
                #random action
            else:
                #self.A=max(range(len(self.Q)),key=self.Q.__getitem__)
                self.A=np.argmax(self.Q)
                #choose highest action value
            self.R=self.the_armed_bandit.arm_s_action_value(self.A)
                
            pltdt_rewards[step] += self.R
            pltdt_optimpercent[step] += \
                1 if self.the_armed_bandit.is_optimal_action(self.A) else 0
            self.N[self.A]=self.N[self.A]+1.0
            self.Q[self.A]= self.Q[self.A] + (
                                (1 / (self.N[self.A])) * 
                                (self.R-self.Q[self.A]))

class ASimpleBanditAlgorithmStaticBanditRunner:

    def __init__(self):
        self.runs=RunsHyperparameter().read_runs()
        self.steps=StepsHyperparameter().read_steps()
        self.bandit_arms_count=BanditArmsCountHyperparameter().read_bandit_arms_count()
        self.pltdt_rewards=np.zeros((3, self.steps))
        self.pltdt_optimpercent=np.zeros((3, self.steps))
        self.epsilon=(0.0, 0.01, 0.1)
        self.plotter=ASimpleBanditAlgorithmPlotter(
                        runs=self.runs,
                        steps=self.steps)

    def run(self):
        self.pltdt_index=-1
        self.the_armed_bandit=StaticArmedBandit(
                                    arms_count=self.bandit_arms_count,
                                    is_random_walk=False)
        for epsilon in self.epsilon:
            self.pltdt_index += 1
            for run in range(self.runs):
                self.algo=ASimpleBanditAlgorithm(
                    steps=self.steps,
                    epsilon=epsilon,
                    the_armed_bandit=self.the_armed_bandit,
                    arms_count=self.bandit_arms_count)
                self.algo.run(
                    pltdt_rewards=self.pltdt_rewards[self.pltdt_index],
                    pltdt_optimpercent=self.pltdt_optimpercent[self.pltdt_index])
                self.the_armed_bandit.reset()
            
        self.plotter.plot(self.pltdt_rewards, self.pltdt_optimpercent)

class DynamicVsFixedStepSizeBanditAlgoPlotter:

    def __init__(self, runs, steps):
        self.runs=runs
        self.steps=steps

    def plot(self, pltdt_fixed_step_size_algo_rewards,
                pltdt_fixed_step_size_algo_optimpercent,
                pltdt_dynamic_step_size_algo_rewards,
                pltdt_dynamic_step_size_algo_optimpercent):

        pltdt_fixed_step_size_algo_optimpercent=\
            pltdt_fixed_step_size_algo_optimpercent.cumsum()
        pltdt_dynamic_step_size_algo_optimpercent=\
            pltdt_dynamic_step_size_algo_optimpercent.cumsum()
        
        pltdt_fixed_step_size_algo_rewards /= self.runs
        pltdt_dynamic_step_size_algo_rewards /= self.runs
        
        for step in range(self.steps):
            pltdt_fixed_step_size_algo_optimpercent[step] /=\
                                                            (self.runs * (step+1))
            pltdt_dynamic_step_size_algo_optimpercent[step] /=\
                                                            (self.runs * (step+1))
        
        plt.figure()
        plt.plot(
            pltdt_fixed_step_size_algo_rewards, label='static rewards')
        plt.plot(
            pltdt_dynamic_step_size_algo_rewards, label='random walk rewards')
        plt.legend(loc='lower right')
        plt.xlabel('Steps')
        plt.ylabel('Average reward')
        plt.savefig('static_vs_random_walk_bandit_rewards.pdf')

        plt.figure()
        plt.plot(
            pltdt_fixed_step_size_algo_optimpercent,
            label='static optimal percent')
        plt.plot(
            pltdt_dynamic_step_size_algo_optimpercent,
            label='random walk optimal percent')
        plt.legend(loc='lower right')
        plt.xlabel('Steps')
        plt.ylabel('% Optimal action')
        plt.savefig(
            'static_vs_random_walk_bandit_optimal_percent.pdf')

class FixedStepSizeBanditAlgo:

    def __init__(self, alpha, steps, epsilon, the_armed_bandit, arms_count):
        self.alpha=alpha
        self.epsilon=epsilon
        self.steps=steps
        self.arms_count=arms_count
        self.the_armed_bandit=the_armed_bandit
        self.Q=np.zeros(self.arms_count)
        self.N=np.zeros(self.arms_count)

    def run(self, pltdt_rewards, pltdt_optimpercent):
        for step in range(self.steps):
            sample=random.uniform(0.0,1.0)
            if sample < self.epsilon :
                self.A=random.randint(0 , (self.arms_count-1))
                #random action
            else:
                #self.A=max(range(len(self.Q)),key=self.Q.__getitem__)
                self.A=np.argmax(self.Q)
                #choose highest action value
            self.R=self.the_armed_bandit.arm_s_action_value(self.A)
                
            pltdt_rewards[step] += self.R
            pltdt_optimpercent[step] += \
                1 if self.the_armed_bandit.is_optimal_action(self.A) else 0

            #pdb.set_trace()
            self.Q[self.A]= self.Q[self.A] + (
                                self.alpha * 
                                (self.R-self.Q[self.A]))

class DynamicVsFixedStepSizeBanditRndWlkAlgoRunner:

    def __init__(self):
        self.runs=RunsHyperparameter().read_runs()
        self.steps=StepsHyperparameter().read_steps()
        self.bandit_arms_count=BanditArmsCountHyperparameter().read_bandit_arms_count()
        self.alpha=AlphaHyperparameter().read_alpha()
        self.pltdt_dynamic_step_size_algo_rewards=np.zeros(self.steps)
        self.pltdt_fixed_step_size_algo_rewards=np.zeros(self.steps)
        self.pltdt_dynamic_step_size_algo_optimpercent=np.zeros(self.steps)
        self.pltdt_fixed_step_size_algo_optimpercent=np.zeros(self.steps)
        self.epsilon=0.1
        self.static_armed_bandit=StaticArmedBandit(
                                    arms_count=self.bandit_arms_count,
                                    is_random_walk=False)
        self.rndwlk_armed_bandit=StaticArmedBandit(
                                    arms_count=self.bandit_arms_count,
                                    is_random_walk=True)
        self.plotter=DynamicVsFixedStepSizeBanditAlgoPlotter(
                        runs=self.runs,
                        steps=self.steps)

    def run(self):
        for run in range(self.runs):
            self.dynamic_step_size_algo=ASimpleBanditAlgorithm(
                steps=self.steps,
                epsilon=self.epsilon,
                the_armed_bandit=self.static_armed_bandit,
                arms_count=self.bandit_arms_count)
            self.dynamic_step_size_algo.run(
                self.pltdt_dynamic_step_size_algo_rewards,
                self.pltdt_dynamic_step_size_algo_optimpercent)
            self.static_armed_bandit.reset()
            self.fixed_step_size_algo=FixedStepSizeBanditAlgo(
                alpha=self.alpha,
                steps=self.steps,
                epsilon=self.epsilon,
                the_armed_bandit=self.rndwlk_armed_bandit,
                arms_count=self.bandit_arms_count)
            self.fixed_step_size_algo.run(
                self.pltdt_fixed_step_size_algo_rewards,
                self.pltdt_fixed_step_size_algo_optimpercent)
            self.rndwlk_armed_bandit.reset()
            
        self.plotter.plot(self.pltdt_fixed_step_size_algo_rewards,
                            self.pltdt_fixed_step_size_algo_optimpercent,
                            self.pltdt_dynamic_step_size_algo_rewards,
                            self.pltdt_dynamic_step_size_algo_optimpercent)

class LinRegrPlotter:

    def plot_lin_reg_1var_input_data(self, np_data_array, x_label, y_label):
        plt.figure()
        plt.scatter(np_data_array[:,0], np_data_array[:,1])
        plt.xlabel(x_label)
        plt.ylabel(y_label)
        plt.savefig('lin_regr_input_data_scatter_plot.pdf')

    def plot_lin_reg_1var_regr_line(self):
        #TODO
        pass

class LinRegrOneVarComputation:

    def __init__(self):
        pass

    def lin_regr_one_var_cost_function(self, data, theta0, theta1):
        #J(theta0,theta1)=sum_from_i=1_to_i=m(1/(2*m))((htheta(xi)-yi)^2)
        self.m=data.shape[0]
        self.cost=0
        for i in range(self.m):
            self.cost += (1/(2*self.m))*((theta0+theta1*data[i][0]-data[i][1]) ** 2)
        return self.cost

class LinRegrOneVarRunner:
    """
m - number of training samples
x y - one training sample
xi yi - ith training sample
hypothesis - maps from x's to y's
htheta(x)=theta0+theta1*x
theta0 theta1 - parameters of the model
minimize over theta0 theta1:
    (htheta(x)-y)^2
    J(theta0,theta1)=sum_from_i=1_to_i=m(1/(2*m))((htheta(xi)-yi)^2)
    J(theta0,theta1) - cost function
outline:
    choose some theta0, theta1 ; for example to 0
    keep changing theta0, theta1 to reduce J(theta0, theta1)
    end up at a minimum
gradient descent algorithm
    repeat until convergence:
        thetaj := thetaj-alpha*(d/dthetaj)J(theta0, theta1) for j=0 and j=1
gradient descent for linear regresion
    (d/dthetaj)J(theta0,theta1)=(d/dthetaj)(1/2*m)sum_from_i=1_to_i=m((theta0+theta1*xi-yi)^2)
    theta0:
        lecture 2.1
        https://www.youtube.com/playlist?list=PLLssT5z_DsK-h9vYZkQkYNWcItqhlRJLN
        https://www.youtube.com/watch?v=GtSf2T6Co80 at 3:05
    """
    def __init__(self):
        self.plotter=LinRegrPlotter()
        self.computation=LinRegrOneVarComputation()

    def run(self):
        #self.file_name=input('CSV file name:')
        self.file_name = "/home/branco/dev/documentation/PROGRAMMING/gamedev/AI_resources/machine-learning-programming-assignments-coursera-andrew-ng/machine-learning-ex1/ex1/ex1data1.txt"
        #self.x_axis_name=input('X axis data name:')
        self.x_axis_name = "population in 10 thousands"
        #self.y_axis_name=input('Y axis data name:')
        self.y_axis_name = "profit in 10 thousand dollars"
        self.lin_reg_data=np.genfromtxt(self.file_name, delimiter=',')
        self.plotter.plot_lin_reg_1var_input_data(
                self.lin_reg_data,
                self.x_axis_name,
                self.y_axis_name)
        self.computation.lin_regr_one_var_cost_function(self.lin_reg_data)

class InitialGreedyExplorationVsEpsilonGreedyPlotter:

    #TODO not modified properly
    def __init__(self, runs, steps):
        self.runs=runs
        self.steps=steps

    def plot(self, pltdt_initial_exploration_algo_rewards,
                pltdt_realistic_eps_greedy_algo_rewards,
                pltdt_initial_exploration_algo_optimpercent,
                pltdt_realistic_eps_greedy_algo_optimpercent):

        pltdt_initial_exploration_algo_optimpercent=\
            pltdt_initial_exploration_algo_optimpercent.cumsum()
        pltdt_realistic_eps_greedy_algo_optimpercent=\
            pltdt_realistic_eps_greedy_algo_optimpercent.cumsum()
        
        pltdt_initial_exploration_algo_rewards /= self.runs
        pltdt_realistic_eps_greedy_algo_rewards /= self.runs
        
        for step in range(self.steps):
            pltdt_initial_exploration_algo_optimpercent[step] /=\
                                                            (self.runs * (step+1))
            pltdt_realistic_eps_greedy_algo_optimpercent[step] /=\
                                                            (self.runs * (step+1))
        
        plt.figure()
        plt.plot(
            pltdt_initial_exploration_algo_rewards,
            label='initial exploration rewards')
        plt.plot(
            pltdt_realistic_eps_greedy_algo_rewards,
            label='realistic epsilon greedy rewards')
        plt.legend(loc='lower right')
        plt.xlabel('Steps')
        plt.ylabel('Average reward')
        plt.savefig('initial_exploration_vs_realistic_eps_greedy_rewards.pdf')

        plt.figure()
        plt.plot(
            pltdt_initial_exploration_algo_optimpercent,
            label='initial exploration optimal percent')
        plt.plot(
            pltdt_realistic_eps_greedy_algo_optimpercent,
            label='realistic epsilon greedy optimal percent')
        plt.legend(loc='lower right')
        plt.xlabel('Steps')
        plt.ylabel('% Optimal action')
        plt.savefig(
            'initial_exploration_vs_realistic_epsilon_greedy_optimal_percent.pdf')

class GreedyInitialExplorationBanditAlgo:

    def __init__(self, steps, the_armed_bandit, arms_count, exploration_value):
        self.steps=steps
        self.arms_count=arms_count
        self.the_armed_bandit=the_armed_bandit
        self.Q=np.full(self.arms_count, exploration_value)
        self.N=np.zeros(self.arms_count)

    def run(self, pltdt_rewards, pltdt_optimpercent):
        for step in range(self.steps):
            self.A=np.argmax(self.Q)
            #^choose highest action value
            self.R=self.the_armed_bandit.arm_s_action_value(self.A)
                
            pltdt_rewards[step] += self.R
            pltdt_optimpercent[step] += \
                1 if self.the_armed_bandit.is_optimal_action(self.A) else 0
            self.N[self.A]=self.N[self.A]+1.0
            self.Q[self.A]= self.Q[self.A] + (
                                (1 / (self.N[self.A])) * 
                                (self.R-self.Q[self.A]))


class InitialExplorationOptimisticGreedyRunner:
#TODO add epsilon greedy default stuff
    def __init__(self):
        self.runs=RunsHyperparameter().read_runs()
        self.steps=StepsHyperparameter().read_steps()
        self.bandit_arms_count=BanditArmsCountHyperparameter().read_bandit_arms_count()
        self.pltdt_initial_exploration_algo_rewards=np.zeros(self.steps)
        self.pltdt_realistic_eps_greedy_algo_rewards=np.zeros(self.steps)
        self.pltdt_initial_exploration_algo_optimpercent=np.zeros(self.steps)
        self.pltdt_realistic_eps_greedy_algo_optimpercent=np.zeros(self.steps)
        self.realistic_epsilon = 0.1
        self.exploration_value = 5.0
        self.armed_bandit=StaticArmedBandit(
                                    arms_count=self.bandit_arms_count,
                                    is_random_walk=False)
        self.plotter=InitialGreedyExplorationVsEpsilonGreedyPlotter (
                        runs=self.runs,
                        steps=self.steps)
    
    def run(self):
        for run in range(self.runs):
            self.initial_exploration_algo = GreedyInitialExplorationBanditAlgo(
                the_armed_bandit = self.armed_bandit,
                arms_count = self.bandit_arms_count,
                exploration_value=self.exploration_value,
                steps = self.steps)
            self.initial_exploration_algo.run(
                self.pltdt_initial_exploration_algo_rewards,
                self.pltdt_initial_exploration_algo_optimpercent)
            self.armed_bandit.reset()
            self.fixed_step_size_algo=ASimpleBanditAlgorithm(
                steps=self.steps,
                epsilon=self.realistic_epsilon,
                the_armed_bandit=self.armed_bandit,
                arms_count=self.bandit_arms_count)
            self.fixed_step_size_algo.run(
                self.pltdt_realistic_eps_greedy_algo_rewards,
                self.pltdt_realistic_eps_greedy_algo_optimpercent)
            self.armed_bandit.reset()
            
        self.plotter.plot(self.pltdt_initial_exploration_algo_rewards,
                            self.pltdt_realistic_eps_greedy_algo_rewards,
                            self.pltdt_initial_exploration_algo_optimpercent,
                            self.pltdt_realistic_eps_greedy_algo_optimpercent)

class CommandLineInterface:

    def __init__(self):
        self.menu_items=self.init_menu_items()
        self.menu_item_cnt=len(self.menu_items)
        #self.snapshot1=None #TODO tracer

    def init_menu_items(self):
        return { 0 : 
                    ('A simple bandit algorithm with static bandit',
                    ASimpleBanditAlgorithmStaticBanditRunner),
                1 :
                    ('Sample averages vs fixed step size with random walk bandit',
                    DynamicVsFixedStepSizeBanditRndWlkAlgoRunner),
                2 : 
                    ('Linear regression with one variable',
                    LinRegrOneVarRunner),
                3 : 
                    ('Bandit algorithm with optimistic greedy initial exploration',
                    InitialExplorationOptimisticGreedyRunner),

                4 : 
                    ('Exit program',
                    ())}

    def show_menu_items(self):
        print('\n')
        for index in range(self.menu_item_cnt):
            (menu_item_text, _)=self.menu_items[index]
            print(str(index) + ' ' +  menu_item_text)

    def menu_item_selection(self):
        invalid=False
        selected_item=()
        
        try:
            selected_item=int(input('Select option:'))
        except ValueError:
            invalid=True
        
        if (selected_item == () or
                selected_item < 0 or
                selected_item >= self.menu_item_cnt):
            invalid=True

        if invalid:
            input(
                'Please input an integer between ' + 
                str(0) + ' and ' + str(self.menu_item_cnt-1) +  
                ' for the desired menu selection')
            return False #but do not exit program

        if selected_item == self.menu_item_cnt-1:
            return True #exit program

        (algo_name, algo_entry_class)=self.menu_items[selected_item]
        print('\nExecuting ' + algo_name)
        algo_entry_class().run()

        #self.snapshot2=tm.take_snapshot() #TODO tracer
        #if self.snapshot1 != None:
            #top_stats=self.snapshot2.compare_to(self.snapshot1, 'lineno')
            #print("Differences:")
            #for stat in top_stats[:10]:
                #print(stat)
            #input("Continue program")
        #self.snapshot1=self.snapshot2

        return False #do not exit program
    
    def menu_loop(self):
        while True:
            self.show_menu_items()
            exit=self.menu_item_selection()
            if exit:
                print('\nClosing program')
                break

def main():
    cmdl_interface = CommandLineInterface()
    cmdl_interface.menu_loop()

if __name__ == "__main__":
    main()

