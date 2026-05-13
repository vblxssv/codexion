/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:45:17 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/11 22:30:59 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "time_utils.h"
#include "context.h"
#include "args.h"
#include "p_queue.h"
#include "dongle.h"
#include "scheduler.h"
#include "monitor_r.h"


int main(int argc, char **argv)
{
    t_args      args;
    t_context   context;
    pthread_t   scheduler_thread;
    pthread_t   monitor_thread; // Добавляем поток монитора
    int         i;

    if (!ft_parse_args(argc, argv, &args))
    {
        printf("Error Parsing\n");
        return (1);
    }

    // 1. Инициализация контекста
    context.args = args;
    pthread_mutex_init(&context.state_mutex, NULL);
    context.is_running = true;
    
    // Инициализируем ресурсы
    context.dongles = ft_init_dongles(args.number_of_coders, args.scheduler);
    context.coders = ft_init_coders(&context);
    
    // Засекаем время СТРОГО перед запуском потоков
    context.start_time = ft_get_current_time();

    // 2. Запуск потоков
    // Сначала кодеры
    for (i = 0; i < args.number_of_coders; i++)
        pthread_create(&context.coders[i].thread, NULL, ft_live_life, &context.coders[i]);

    // Затем скедулер
    pthread_create(&scheduler_thread, NULL, ft_scheduler_routine, &context);

    // И в конце — монитор, который начнет всех проверять
    pthread_create(&monitor_thread, NULL, ft_monitor_routine, &context);

    // 3. Ожидание завершения
    // Мы ждем только монитор, так как он завершится первым, когда кто-то "сгорит"
    pthread_join(monitor_thread, NULL);

    // ВАЖНО: Будим всех кодеров, чтобы они вышли из cond_wait и увидели, что is_running == false
    for (i = 0; i < args.number_of_coders; i++)
        ft_wake_up(&context.coders[i]);

    // Теперь спокойно собираем все остальные потоки
    for (i = 0; i < args.number_of_coders; i++)
        pthread_join(context.coders[i].thread, NULL);
    pthread_join(scheduler_thread, NULL);

    // 4. Очистка
    ft_free_dongles(context.dongles, context.args.number_of_coders);
    ft_free_coders(context.coders);
    pthread_mutex_destroy(&context.state_mutex);
    
    return (0);
}
