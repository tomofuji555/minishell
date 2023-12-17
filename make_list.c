t_Node	*make_list(int argc, char **argv)
{
	t_Node	*head;
	t_Node	*ptr;
	int		i;

	head = (t_Node *)malloc(sizeof(t_Node));
	if (ptr == NULL)
		return ;
	ptr = head;
	i = 1;
	while (i < argc)
	{
		ptr->next = (t_Node *)malloc(sizeof(t_Node));
		if (ptr->next == NULL)
			return (free_list(head));
		ptr = ptr->next;
		ptr->val = ps_atol(argv[i]);
		i++;
	}
	ptr->next = NULL;
	return (head);
}

int main()
{
	char **strs1 = {"ls"}
}