CREATE PROCEDURE [dbo].[set_user_match_info]
	@xmlDoc xml
AS
	--表变量
	declare @user_id bigint, @plan_id int, @match_id bigint, @plan_name varchar(50),  @match_rank int, @end_date bigint
	--临时变量
	declare @count int, @i int, @parm nvarchar(10), @sql nvarchar(200)
	set @i = 1
	set @count = @xmlDoc.value('(/count)[1]', 'int')
	while @i <= @count
	begin
		set @i = @i + 1;	--循环次数+1
		set @parm = @i;
		--取user_id
		set @sql = N'select @user_id = @xmlDoc.value(''(/data/user_id)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@user_id bigint output, @xmlDoc xml',@user_id output, @xmlDoc
		--取plan_id
		set @sql = N'select @plan_id = @xmlDoc.value(''(/data/plan_id)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@plan_id int output, @xmlDoc xml',@plan_id output, @xmlDoc
		--取match_id
		set @sql = N'select @match_id = @xmlDoc.value(''(/data/match_id)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@match_id bigint output, @xmlDoc xml',@match_id output, @xmlDoc
		--取plan_name
		set @sql = N'select @plan_name = @xmlDoc.value(''(/data/plan_name)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@plan_name varchar(50) output, @xmlDoc xml',@plan_name output, @xmlDoc
		--取match_date
		set @sql = N'select @match_rank = @xmlDoc.value(''(/data/match_rank)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@match_rank int output, @xmlDoc xml',@match_rank output, @xmlDoc
		--取end_date
		set @sql = N'select @end_date = @xmlDoc.value(''(/data/end_date)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@end_date bigint output, @xmlDoc xml',@end_date output, @xmlDoc

		insert into user_match_info(user_id, plan_id, match_id, plan_name, match_rank, end_date)
			values(@user_id, @plan_id, @match_id, @plan_name, @match_rank, @end_date)

	end
RETURN 0
