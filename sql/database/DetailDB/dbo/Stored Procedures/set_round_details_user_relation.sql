CREATE PROCEDURE [dbo].[set_round_details_user_relation]
	@xmlDoc xml
AS
	--表变量
	declare @plan_id int, @match_id bigint, @round_id varchar(50), @user_id bigint, @round_result int
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
		--取round_id
		set @sql = N'select @round_id = @xmlDoc.value(''(/data/round_id)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@round_id varchar(50) output, @xmlDoc xml',@round_id output, @xmlDoc
		--取user_id
		set @sql = N'select @user_id = @xmlDoc.value(''(/data/user_id)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@user_id bigint output, @xmlDoc xml',@user_id output, @xmlDoc
		--取match_date
		set @sql = N'select @round_result = @xmlDoc.value(''(/data/round_result)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@round_result bigint output, @xmlDoc xml',@round_result output, @xmlDoc

		insert into round_details_user_relation(plan_id, match_id, round_id, user_id, round_result)
			values(@plan_id, @match_id, @round_id, @user_id, @round_result)

	end
RETURN 0
