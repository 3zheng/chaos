CREATE PROCEDURE [dbo].[set_online_time_details]
	@xmlDoc xml
AS
	--表变量
	declare @user_id bigint, @ip_address varchar(50), @online_start_time bigint
	declare	@online_end_time bigint, @plan_id int, @match_id bigint
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
		--取ip_address
		set @sql = N'select @ip_address = @xmlDoc.value(''(/data/ip_address)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@ip_address varchar(50) output, @xmlDoc xml',@ip_address output, @xmlDoc
		--取online_start_time
		set @sql = N'select @online_start_time = @xmlDoc.value(''(/data/online_start_time)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@online_start_time bigint output, @xmlDoc xml',@online_start_time output, @xmlDoc
		--取online_end_time
		set @sql = N'select @online_end_time = @xmlDoc.value(''(/data/online_end_time)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@online_end_time bigint output, @xmlDoc xml',@online_end_time output, @xmlDoc
		--取plan_id
		set @sql = N'select @plan_id = @xmlDoc.value(''(/data/plan_id)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@plan_id int output, @xmlDoc xml',@plan_id output, @xmlDoc
		--取match_id
		set @sql = N'select @match_id = @xmlDoc.value(''(/data/match_id)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@match_id bigint output, @xmlDoc xml',@match_id output, @xmlDoc

		insert into online_time_detail(user_id, ip_address, online_start_time, online_end_time, plan_id, match_id)
			values(@user_id, @ip_address, @online_start_time, @online_end_time, @plan_id, @match_id)

	end
RETURN 0