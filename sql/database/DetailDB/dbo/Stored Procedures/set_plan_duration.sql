CREATE PROCEDURE [dbo].[set_plan_duration]
	@xmlDoc xml
AS
	--表变量
	declare @plan_id int, @match_id bigint, @mass_election_duration int, @elimination_duration int, @match_date bigint
	--临时变量
	declare @count int, @i int, @parm nvarchar(10), @sql nvarchar(200)
	set @i = 1
	set @count = @xmlDoc.value('(/count)[1]', 'int')
	while @i <= @count
	begin
		set @i = @i + 1;	--循环次数+1
		set @parm = @i;
		--取plan_id
		set @sql = N'select @plan_id = @xmlDoc.value(''(/data/plan_id)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@plan_id int output, @xmlDoc xml',@plan_id output, @xmlDoc
		--取match_id
		set @sql = N'select @match_id = @xmlDoc.value(''(/data/match_id)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@match_id bigint output, @xmlDoc xml',@match_id output, @xmlDoc
		--取mass_election_duration海选阶段耗时
		set @sql = N'select @mass_election_duration = @xmlDoc.value(''(/data/mass_election_duration)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@mass_election_duration int output, @xmlDoc xml',@mass_election_duration output, @xmlDoc
		--取elimination_duration淘汰赛阶段耗时
		set @sql = N'select @elimination_duration = @xmlDoc.value(''(/data/elimination_duration)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@elimination_duration int output, @xmlDoc xml',@elimination_duration output, @xmlDoc
		--取match_date
		set @sql = N'select @match_date = @xmlDoc.value(''(/data/match_date)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@match_date bigint output, @xmlDoc xml',@match_date output, @xmlDoc

		insert into plan_duration(plan_id, match_id, mass_election_duration, elimination_duration, match_date)
			values(@plan_id, @match_id, @mass_election_duration, @elimination_duration, @match_date)

	end
RETURN 0
