Проект, создающий расписание для пользователя.
На вход программе подаётся часть расписания пользователя, которую он не может изменить(учёба в институте/работа/дежурство и тд), граф расстояний между различными местам(расстояние измеряется во временных интервалах, которые необходимо затратить, чтобы переместиться из одного места в другое). Кроме того на вход подаётся та часть расписания пользователя, которую нужно вставить в сетку расписания, про которую известна длительность кждого события и его место проведения и время, до которого его необходиом сделать (дедлайн).
На выходе программа отдаёт готовую полную сетку расписания с учётом следующих критериев:
1) Максимизируется время отдыха на выходных и минимизируется таковое в будни
2) Крайне нежелательно расписание, при котором для выполнения свободной части расписания необходимо совершать дополнительную поездку до другого места. (Например, у нас есть дело в институте "Подать документы на проездной", но во вторник пользователь не учится в институте, а работает на другом конце Москвы. Тогда желательнее будет это дело перенести на среду, когда пользователь учится в институте, чтобы не совершать дополнительную поездку).
3) Все задания должны быть выполнены до дедлайна.
4) События в расписании не должны пересекаться.

Данная программа использует генетический алгоритм для создания сетки расписания с учётом вышеуказанных требований.
